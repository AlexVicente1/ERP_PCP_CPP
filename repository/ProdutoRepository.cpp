#include "ProdutoRepository.h"

#include <algorithm>

namespace erp::pcp::repository {

ProdutoRepository::ProdutoRepository(core::Database& database) : database_(database) {}

void ProdutoRepository::save(const models::Produto& produto) {
    produtos_.push_back(produto);
    database_.executeQuery("INSERT INTO produtos (...) VALUES (...);");
}

std::optional<models::Produto> ProdutoRepository::findById(int id) const {
    const auto it = std::find_if(produtos_.begin(), produtos_.end(),
                                 [id](const models::Produto& p) { return p.id() == id; });

    if (it == produtos_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::vector<models::Produto> ProdutoRepository::findAll() const { return produtos_; }

std::vector<models::Produto> ProdutoRepository::findProdutosComReposicao() const {
    std::vector<models::Produto> result;
    for (const auto& produto : produtos_) {
        if (produto.precisaReposicao()) {
            result.push_back(produto);
        }
    }
    return result;
}

}  // namespace erp::pcp::repository
