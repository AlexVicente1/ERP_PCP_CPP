#pragma once

#include "../../application/usecases/CreateProductionOrderUseCase.h"
#include "../../application/usecases/DashboardService.h"
#include "../../application/usecases/RegisterChemicalProductUseCase.h"
#include "../../security/auth/AuthService.h"

namespace erp::pcp::presentation::cli {

class CliApp {
public:
    CliApp(application::usecases::RegisterChemicalProductUseCase& registerProduct,
           application::usecases::CreateProductionOrderUseCase& createOrder,
           application::usecases::DashboardService& dashboard, security::auth::AuthService& auth);

    void run();

private:
    application::usecases::RegisterChemicalProductUseCase& registerProduct_;
    application::usecases::CreateProductionOrderUseCase& createOrder_;
    application::usecases::DashboardService& dashboard_;
    security::auth::AuthService& auth_;
};

}
