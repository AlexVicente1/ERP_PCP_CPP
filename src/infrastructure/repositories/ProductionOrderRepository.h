#pragma once

#include <vector>

#include "../../domain/entities/ProductionOrder.h"

namespace erp::pcp::infrastructure::repositories {

class ProductionOrderRepository {
public:
    void save(domain::entities::ProductionOrder order);
    std::vector<domain::entities::ProductionOrder> findAll() const;

private:
    std::vector<domain::entities::ProductionOrder> orders_;
};

}
