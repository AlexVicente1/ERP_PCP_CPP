#include "ProductionOrderRepository.h"

namespace erp::pcp::infrastructure::repositories {

void ProductionOrderRepository::save(domain::entities::ProductionOrder order) {
    orders_.push_back(std::move(order));
}

std::vector<domain::entities::ProductionOrder> ProductionOrderRepository::findAll() const {
    return orders_;
}

}
