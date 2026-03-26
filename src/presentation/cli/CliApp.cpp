#include "CliApp.h"

#include <iostream>

#include "../../application/dto/ChemicalProductDto.h"
#include "../../domain/enums/Role.h"

namespace erp::pcp::presentation::cli {

CliApp::CliApp(application::usecases::RegisterChemicalProductUseCase& registerProduct,
               application::usecases::CreateProductionOrderUseCase& createOrder,
               application::usecases::DashboardService& dashboard, security::auth::AuthService& auth)
    : registerProduct_(registerProduct), createOrder_(createOrder), dashboard_(dashboard), auth_(auth) {}

void CliApp::run() {
    std::string user, pass;
    std::cout << "ERP PCP - Chemical Industry\nUser: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;
    if (!auth_.login(user, pass)) {
        std::cout << "Access denied.\n";
        return;
    }

    if (!auth_.authorize(domain::enums::Role::ChemicalEngineer)) {
        std::cout << "Insufficient role.\n";
        return;
    }

    application::dto::ChemicalProductDto dto;
    dto.id = 100;
    dto.code = "CHEM-ACETONE";
    dto.name = "Acetone Industrial";
    dto.apiLookupName = "acetone";
    dto.density = 0.79;
    dto.initialStock = 1000.0;
    dto.minimumStock = 250.0;
    registerProduct_.execute(dto, auth_.currentUser());

    const bool created = createOrder_.execute(5001, dto.id, 200.0, auth_.currentUser());
    std::cout << (created ? "Production order created.\n" : "Order blocked - purchase suggested.\n");

    std::cout << dashboard_.buildIndustrialKpiSummary() << "\n";
}

}
