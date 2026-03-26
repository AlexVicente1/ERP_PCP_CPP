#include "CreateProductionOrderUseCase.h"

#include "../../domain/entities/ProductionOrder.h"
#include "../../domain/enums/BatchStatus.h"
#include "../../shared/utils/DateTime.h"

namespace erp::pcp::application::usecases {

CreateProductionOrderUseCase::CreateProductionOrderUseCase(
    infrastructure::repositories::ChemicalProductRepository& productRepo,
    infrastructure::repositories::ProductionOrderRepository& orderRepo,
    security::audit::AuditLogger& audit)
    : productRepo_(productRepo), orderRepo_(orderRepo), audit_(audit) {}

bool CreateProductionOrderUseCase::execute(int orderId, int productId, double quantity,
                                           const std::string& user) {
    auto product = productRepo_.findById(productId);
    if (!product.has_value() || product.value() == nullptr) return false;

    if (!product.value()->consume(quantity)) {
        audit_.record(user, "MRP purchase suggestion for product " + std::to_string(productId),
                      shared::utils::now());
        return false;
    }

    domain::entities::ProductionOrder order(orderId, productId, quantity, user);
    order.progressTo(domain::enums::BatchStatus::InProduction);
    order.registerConsumption(quantity);
    order.registerLoss(quantity * 0.02);  // 2% standard process loss
    order.progressTo(domain::enums::BatchStatus::Finished);
    orderRepo_.save(std::move(order));

    audit_.record(user, "Created production order " + std::to_string(orderId), shared::utils::now());
    return true;
}

}
