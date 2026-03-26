#pragma once

#include <string>

#include "../enums/BatchStatus.h"

namespace erp::pcp::domain::entities {

class ProductionOrder {
public:
    ProductionOrder(int id, int productId, double plannedQuantity, std::string createdBy);

    int id() const;
    int productId() const;
    double plannedQuantity() const;
    double consumedRawMaterial() const;
    double losses() const;
    double efficiency() const;
    enums::BatchStatus status() const;
    const std::string& createdBy() const;

    void progressTo(enums::BatchStatus nextStatus);
    void registerConsumption(double quantity);
    void registerLoss(double quantity);

private:
    int id_;
    int productId_;
    double plannedQuantity_;
    double consumedRawMaterial_{0.0};
    double losses_{0.0};
    double efficiency_{0.0};
    enums::BatchStatus status_{enums::BatchStatus::Created};
    std::string createdBy_;
};

}
