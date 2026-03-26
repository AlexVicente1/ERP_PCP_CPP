#pragma once

#include <optional>
#include <vector>

#include "../../domain/entities/ChemicalProduct.h"

namespace erp::pcp::infrastructure::repositories {

class ChemicalProductRepository {
public:
    void save(domain::entities::ChemicalProduct product);
    std::optional<domain::entities::ChemicalProduct*> findById(int id);
    std::vector<domain::entities::ChemicalProduct> findAll() const;

private:
    std::vector<domain::entities::ChemicalProduct> products_;
};

}
