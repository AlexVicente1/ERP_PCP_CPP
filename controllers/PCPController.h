#pragma once

#include <iostream>
#include <limits>

#include "../services/PCPService.h"
#include "../utils/Logger.h"

namespace erp::pcp::controllers {

class PCPController {
public:
    explicit PCPController(services::PCPService& pcpService) : pcpService_(pcpService) {}
    void run();

private:
    void exibirMenu() const;
    void cadastrarProduto();
    void criarOrdem();
    void listarProdutos() const;
    void listarOrdens() const;

    services::PCPService& pcpService_;
};

inline void PCPController::run() {
    pcpService_.carregarDados();
    int opcao = -1;
    while (opcao != 0) {
        exibirMenu();
        std::cin >> opcao;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils::Logger::error("Opcao invalida.");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                criarOrdem();
                break;
            case 3:
                listarProdutos();
                break;
            case 4:
                listarOrdens();
                break;
            case 0:
                pcpService_.salvarDados();
                utils::Logger::info("Encerrando sistema PCP.");
                break;
            default:
                utils::Logger::error("Opcao nao existe.");
                break;
        }
    }
}

inline void PCPController::exibirMenu() const {
    std::cout << "\n===== ERP PCP (Console) =====\n";
    std::cout << "1 - Cadastrar produto\n";
    std::cout << "2 - Criar ordem de producao\n";
    std::cout << "3 - Listar produtos\n";
    std::cout << "4 - Listar ordens de producao\n";
    std::cout << "0 - Sair\n";
    std::cout << "Escolha: ";
}

inline void PCPController::cadastrarProduto() {
    int id = 0;
    int estoqueAtual = 0;
    int estoqueMinimo = 0;
    std::string codigo;
    std::string descricao;

    std::cout << "ID: ";
    std::cin >> id;
    std::cout << "Codigo: ";
    std::cin >> codigo;
    std::cout << "Descricao (sem espacos): ";
    std::cin >> descricao;
    std::cout << "Estoque atual: ";
    std::cin >> estoqueAtual;
    std::cout << "Estoque minimo: ";
    std::cin >> estoqueMinimo;

    pcpService_.cadastrarProduto(
        models::Produto(id, codigo, descricao, estoqueAtual, estoqueMinimo));
}

inline void PCPController::criarOrdem() {
    int numero = 0;
    int produtoId = 0;
    int quantidade = 0;

    std::cout << "Numero da ordem: ";
    std::cin >> numero;
    std::cout << "ID do produto: ";
    std::cin >> produtoId;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    const auto ordem = pcpService_.criarOrdemProducao(numero, produtoId, quantidade);
    if (!ordem.has_value()) {
        utils::Logger::error("Falha ao criar ordem.");
    }
}

inline void PCPController::listarProdutos() const {
    const auto produtos = pcpService_.listarProdutos();
    std::cout << "\n--- Produtos ---\n";
    for (const auto& p : produtos) {
        std::cout << "ID: " << p.id() << " | Codigo: " << p.codigo()
                  << " | Desc: " << p.descricao() << " | Estoque: " << p.estoqueAtual()
                  << " | Min: " << p.estoqueMinimo() << '\n';
    }

    const auto reposicao = pcpService_.produtosParaPlanejamento();
    std::cout << "Produtos com reposicao pendente: " << reposicao.size() << '\n';
}

inline void PCPController::listarOrdens() const {
    const auto ordens = pcpService_.listarOrdens();
    std::cout << "\n--- Ordens ---\n";
    for (const auto& o : ordens) {
        std::cout << "Ordem #" << o.numero() << " | Produto ID: " << o.produtoId()
                  << " | Qtde: " << o.quantidadePlanejada() << '\n';
    }
}

}  // namespace erp::pcp::controllers
