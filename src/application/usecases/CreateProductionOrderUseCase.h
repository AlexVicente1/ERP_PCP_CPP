#pragma once

#include "../../infrastructure/repositories/ChemicalProductRepository.h"
#include "../../infrastructure/repositories/ProductionOrderRepository.h"
#include "../../security/audit/AuditLogger.h"

namespace erp::pcp::application::usecases {

class CreateProductionOrderUseCase {
public:
    CreateProductionOrderUseCase(infrastructure::repositories::ChemicalProductRepository& productRepo,
                                 infrastructure::repositories::ProductionOrderRepository& orderRepo,
                                 security::audit::AuditLogger& audit);

    bool execute(int orderId, int productId, double quantity, const std::string& user);

private:
    infrastructure::repositories::ChemicalProductRepository& productRepo_;
    infrastructure::repositories::ProductionOrderRepository& orderRepo_;
    security::audit::AuditLogger& audit_;
};

}
