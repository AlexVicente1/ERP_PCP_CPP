#pragma once

#include <string>

#include "../../infrastructure/repositories/ChemicalProductRepository.h"
#include "../../infrastructure/repositories/ProductionOrderRepository.h"

namespace erp::pcp::application::usecases {

class DashboardService {
public:
    DashboardService(infrastructure::repositories::ChemicalProductRepository& productRepo,
                     infrastructure::repositories::ProductionOrderRepository& orderRepo);

    std::string buildIndustrialKpiSummary() const;

private:
    infrastructure::repositories::ChemicalProductRepository& productRepo_;
    infrastructure::repositories::ProductionOrderRepository& orderRepo_;
};

}
