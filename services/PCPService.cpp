#include "PCPService.h"

namespace erp::pcp::services {

PCPService::PCPService(repository::ProdutoRepository& produtoRepository)
    : produtoRepository_(produtoRepository) {}

void PCPService::cadastrarProduto(const models::Produto& produto) {
    produtoRepository_.save(produto);
}

std::vector<models::Produto> PCPService::listarProdutos() const {
    return produtoRepository_.findAll();
}

std::vector<models::Produto> PCPService::produtosParaPlanejamento() const {
    return produtoRepository_.findProdutosComReposicao();
}

}  // namespace erp::pcp::services
