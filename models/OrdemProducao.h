#pragma once

#include <string>

namespace erp::pcp::models {

enum class OrdemStatus { Planejada, EmAndamento, Finalizada, Cancelada };

class OrdemProducao {
public:
    OrdemProducao(int numero, int produtoId, int quantidadePlanejada)
        : numero_(numero), produtoId_(produtoId), quantidadePlanejada_(quantidadePlanejada) {}

    int numero() const { return numero_; }
    int produtoId() const { return produtoId_; }
    int quantidadePlanejada() const { return quantidadePlanejada_; }
    OrdemStatus status() const { return status_; }
    const std::string& observacao() const { return observacao_; }

    void iniciar() { status_ = OrdemStatus::EmAndamento; }
    void finalizar() { status_ = OrdemStatus::Finalizada; }
    void cancelar(std::string observacao = "") {
        status_ = OrdemStatus::Cancelada;
        observacao_ = std::move(observacao);
    }

private:
    int numero_;
    int produtoId_;
    int quantidadePlanejada_;
    OrdemStatus status_{OrdemStatus::Planejada};
    std::string observacao_;
};

}  // namespace erp::pcp::models
