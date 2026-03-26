#include "ProductionOrder.h"

namespace erp::pcp::domain::entities {

ProductionOrder::ProductionOrder(int id, int productId, double plannedQuantity, std::string createdBy)
    : id_(id), productId_(productId), plannedQuantity_(plannedQuantity), createdBy_(std::move(createdBy)) {}

int ProductionOrder::id() const { return id_; }
int ProductionOrder::productId() const { return productId_; }
double ProductionOrder::plannedQuantity() const { return plannedQuantity_; }
double ProductionOrder::consumedRawMaterial() const { return consumedRawMaterial_; }
double ProductionOrder::losses() const { return losses_; }
double ProductionOrder::efficiency() const { return efficiency_; }
enums::BatchStatus ProductionOrder::status() const { return status_; }
const std::string& ProductionOrder::createdBy() const { return createdBy_; }

void ProductionOrder::progressTo(enums::BatchStatus nextStatus) { status_ = nextStatus; }
void ProductionOrder::registerConsumption(double quantity) {
    if (quantity > 0.0) consumedRawMaterial_ += quantity;
}
void ProductionOrder::registerLoss(double quantity) {
    if (quantity > 0.0) losses_ += quantity;
    const double useful = plannedQuantity_ - losses_;
    efficiency_ = plannedQuantity_ > 0.0 ? (useful / plannedQuantity_) * 100.0 : 0.0;
}

}
