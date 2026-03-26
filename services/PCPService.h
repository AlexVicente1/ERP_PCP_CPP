#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include <string>
#include <vector>

#include "../models/OrdemProducao.h"
#include "../models/Produto.h"
#include "../repository/ProdutoRepository.h"
#include "../utils/Logger.h"

namespace erp::pcp::services {

class PCPService {
public:
    explicit PCPService(repository::ProdutoRepository& produtoRepository)
        : produtoRepository_(produtoRepository) {}

    void cadastrarProduto(const models::Produto& produto);
    std::optional<models::OrdemProducao> criarOrdemProducao(int numero, int produtoId, int quantidade);
    std::vector<models::Produto> listarProdutos() const;
    std::vector<models::OrdemProducao> listarOrdens() const;
    std::vector<models::Produto> produtosParaPlanejamento() const;
    void carregarDados();
    void salvarDados() const;

private:
    const std::string produtosFilePath_{"data/produtos.csv"};
    const std::string ordensFilePath_{"data/ordens.csv"};
    repository::ProdutoRepository& produtoRepository_;
    std::vector<models::OrdemProducao> ordens_;
};

inline void PCPService::cadastrarProduto(const models::Produto& produto) {
    produtoRepository_.save(produto);
    utils::Logger::info("Produto cadastrado: " + produto.codigo() + " - " + produto.descricao());
    salvarDados();
}

inline std::optional<models::OrdemProducao> PCPService::criarOrdemProducao(
    int numero, int produtoId, int quantidade) {
    auto produto = produtoRepository_.findByIdForUpdate(produtoId);
    if (!produto.has_value() || produto.value() == nullptr) {
        utils::Logger::error("Produto nao encontrado para a ordem.");
        return std::nullopt;
    }

    if (!produto.value()->reduzirEstoque(quantidade)) {
        utils::Logger::error("Estoque insuficiente para criar ordem de producao.");
        return std::nullopt;
    }

    models::OrdemProducao ordem(numero, produtoId, quantidade);
    ordem.iniciar();
    ordem.finalizar();
    ordens_.push_back(ordem);

    utils::Logger::info("Ordem de producao criada: #" + std::to_string(numero) +
                        " | Produto ID: " + std::to_string(produtoId) +
                        " | Qtde: " + std::to_string(quantidade));
    salvarDados();
    return ordem;
}

inline std::vector<models::Produto> PCPService::listarProdutos() const {
    return produtoRepository_.findAll();
}

inline std::vector<models::OrdemProducao> PCPService::listarOrdens() const { return ordens_; }

inline std::vector<models::Produto> PCPService::produtosParaPlanejamento() const {
    return produtoRepository_.findProdutosComReposicao();
}

inline void PCPService::carregarDados() {
    produtoRepository_.loadFromFile(produtosFilePath_);

    std::ifstream file(ordensFilePath_);
    if (!file.is_open()) {
        utils::Logger::info("Nenhum arquivo de ordens encontrado, iniciando vazio.");
        return;
    }

    ordens_.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string numeroStr, produtoIdStr, quantidadeStr;
        if (!std::getline(ss, numeroStr, ';') || !std::getline(ss, produtoIdStr, ';') ||
            !std::getline(ss, quantidadeStr, ';')) {
            continue;
        }

        models::OrdemProducao ordem(std::stoi(numeroStr), std::stoi(produtoIdStr),
                                    std::stoi(quantidadeStr));
        ordem.iniciar();
        ordem.finalizar();
        ordens_.push_back(ordem);
    }
    utils::Logger::info("Dados carregados com sucesso.");
}

inline void PCPService::salvarDados() const {
    std::filesystem::create_directories("data");
    produtoRepository_.saveToFile(produtosFilePath_);

    std::ofstream file(ordensFilePath_, std::ios::trunc);
    if (!file.is_open()) {
        utils::Logger::error("Falha ao salvar arquivo de ordens.");
        return;
    }

    for (const auto& ordem : ordens_) {
        file << ordem.numero() << ';' << ordem.produtoId() << ';' << ordem.quantidadePlanejada()
             << '\n';
    }
}

}  // namespace erp::pcp::services
