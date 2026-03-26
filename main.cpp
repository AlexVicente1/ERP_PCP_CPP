#include "src/application/usecases/CreateProductionOrderUseCase.h"
#include "src/application/usecases/DashboardService.h"
#include "src/application/usecases/RegisterChemicalProductUseCase.h"
#include "src/infrastructure/api/ChemicalApiClient.h"
#include "src/infrastructure/repositories/ChemicalProductRepository.h"
#include "src/infrastructure/repositories/ProductionOrderRepository.h"
#include "src/presentation/cli/CliApp.h"
#include "src/security/audit/AuditLogger.h"
#include "src/security/auth/AuthService.h"

int main() {
    erp::pcp::infrastructure::repositories::ChemicalProductRepository productRepo;
    erp::pcp::infrastructure::repositories::ProductionOrderRepository orderRepo;
    erp::pcp::infrastructure::api::ChemicalApiClient api;
    erp::pcp::security::audit::AuditLogger audit;
    erp::pcp::security::auth::AuthService auth;

    erp::pcp::application::usecases::RegisterChemicalProductUseCase registerProduct(productRepo, api, audit);
    erp::pcp::application::usecases::CreateProductionOrderUseCase createOrder(productRepo, orderRepo, audit);
    erp::pcp::application::usecases::DashboardService dashboard(productRepo, orderRepo);

    erp::pcp::presentation::cli::CliApp app(registerProduct, createOrder, dashboard, auth);
    app.run();
    return 0;
}
