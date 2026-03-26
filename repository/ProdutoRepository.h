#pragma once

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "../models/Produto.h"

namespace erp::pcp::repository {

class ProdutoRepository {
public:
    ProdutoRepository() = default;
    void save(models::Produto produto) { produtos_.push_back(std::move(produto)); }
    std::optional<models::Produto> findById(int id) const;
    std::optional<models::Produto*> findByIdForUpdate(int id);
    std::vector<models::Produto> findAll() const;
    std::vector<models::Produto> findProdutosComReposicao() const;
    bool loadFromFile(const std::string& filePath);
    bool saveToFile(const std::string& filePath) const;

private:
    std::vector<models::Produto> produtos_;
};

inline std::optional<models::Produto> ProdutoRepository::findById(int id) const {
    for (const auto& produto : produtos_) {
        if (produto.id() == id) {
            return produto;
        }
    }
    return std::nullopt;
}

inline std::optional<models::Produto*> ProdutoRepository::findByIdForUpdate(int id) {
    for (auto& produto : produtos_) {
        if (produto.id() == id) {
            return &produto;
        }
    }
    return std::nullopt;
}

inline std::vector<models::Produto> ProdutoRepository::findAll() const { return produtos_; }

inline std::vector<models::Produto> ProdutoRepository::findProdutosComReposicao() const {
    std::vector<models::Produto> result;
    for (const auto& produto : produtos_) {
        if (produto.precisaReposicao()) {
            result.push_back(produto);
        }
    }
    return result;
}

inline bool ProdutoRepository::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    produtos_.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string idStr, codigo, descricao, estoqueAtualStr, estoqueMinimoStr;

        if (!std::getline(ss, idStr, ';') || !std::getline(ss, codigo, ';') ||
            !std::getline(ss, descricao, ';') || !std::getline(ss, estoqueAtualStr, ';') ||
            !std::getline(ss, estoqueMinimoStr, ';')) {
            continue;
        }

        produtos_.emplace_back(std::stoi(idStr), codigo, descricao, std::stoi(estoqueAtualStr),
                               std::stoi(estoqueMinimoStr));
    }
    return true;
}

inline bool ProdutoRepository::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& produto : produtos_) {
        file << produto.id() << ';' << produto.codigo() << ';' << produto.descricao() << ';'
             << produto.estoqueAtual() << ';' << produto.estoqueMinimo() << '\n';
    }
    return true;
}

}  // namespace erp::pcp::repository
