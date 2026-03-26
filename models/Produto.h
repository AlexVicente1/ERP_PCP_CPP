#pragma once

#include <string>

namespace erp::pcp::models {

class Produto {
public:
    Produto(int id, std::string codigo, std::string descricao, int estoqueAtual, int estoqueMinimo)
        : id_(id),
          codigo_(std::move(codigo)),
          descricao_(std::move(descricao)),
          estoqueAtual_(estoqueAtual),
          estoqueMinimo_(estoqueMinimo) {}

    int id() const { return id_; }
    const std::string& codigo() const { return codigo_; }
    const std::string& descricao() const { return descricao_; }
    int estoqueAtual() const { return estoqueAtual_; }
    int estoqueMinimo() const { return estoqueMinimo_; }

    bool precisaReposicao() const { return estoqueAtual_ < estoqueMinimo_; }
    bool reduzirEstoque(int quantidade) {
        if (quantidade <= 0 || quantidade > estoqueAtual_) {
            return false;
        }
        estoqueAtual_ -= quantidade;
        return true;
    }

private:
    int id_;
    std::string codigo_;
    std::string descricao_;
    int estoqueAtual_;
    int estoqueMinimo_;
};

}  // namespace erp::pcp::models
