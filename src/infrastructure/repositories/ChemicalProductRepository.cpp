#include "ChemicalProductRepository.h"

namespace erp::pcp::infrastructure::repositories {

void ChemicalProductRepository::save(domain::entities::ChemicalProduct product) {
    products_.push_back(std::move(product));
}

std::optional<domain::entities::ChemicalProduct*> ChemicalProductRepository::findById(int id) {
    for (auto& product : products_) {
        if (product.id() == id) return &product;
    }
    return std::nullopt;
}

std::vector<domain::entities::ChemicalProduct> ChemicalProductRepository::findAll() const {
    return products_;
}

}
