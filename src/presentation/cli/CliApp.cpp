#include "CliApp.h"

#include <iostream>
#include <limits>

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

    std::cout << "\nLogin OK. Usuário: " << auth_.currentUser() << "\n";

    while (auth_.isAuthenticated()) {
        std::cout << "\n=== Menu demo (JSON + RBAC) ===\n";
        std::cout << "1) viewDashboard\n";
        std::cout << "2) createOrder\n";
        std::cout << "3) viewReports\n";
        std::cout << "4) deleteOrder (admin)\n";
        std::cout << "5) addUser (admin)\n";
        std::cout << "6) changePassword\n";
        std::cout << "0) logout\n";
        std::cout << "Escolha: ";

        int option = -1;
        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (option == 0) {
            auth_.logout();
            std::cout << "Logout efetuado.\n";
            break;
        }

        auto requireAccess = [&](const std::string& feature) -> bool {
            if (auth_.canAccess(feature)) return true;
            std::cout << "Acesso negado para: " << feature << "\n";
            return false;
        };

        if (option == 1) {
            if (!requireAccess("viewDashboard")) continue;
            std::cout << dashboard_.buildIndustrialKpiSummary() << "\n";
        } else if (option == 2) {
            if (!requireAccess("createOrder")) continue;

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
            std::cout << (created ? "Ordem criada com sucesso.\n" : "Ordem bloqueada - compra sugerida.\n");
        } else if (option == 3) {
            if (!requireAccess("viewReports")) continue;
            std::cout << "Relatórios (demo):\n";
            std::cout << "- Indicadores do painel\n";
            std::cout << "- Logs operacionais\n";
            std::cout << "- Produção e qualidade (em evolução)\n";
        } else if (option == 4) {
            if (!requireAccess("deleteOrder")) continue;
            std::cout << "deleteOrder (demo): apenas Admin pode executar.\n";
        } else if (option == 5) {
            if (!requireAccess("addUser")) continue;
            std::string newUser, newPass, role;
            std::cout << "Novo username: ";
            std::cin >> newUser;
            std::cout << "Nova senha: ";
            std::cin >> newPass;
            std::cout << "Role (Admin/User): ";
            std::cin >> role;
            if (auth_.addUser(newUser, newPass, role)) {
                std::cout << "Usuário criado/atualizado e salvo no JSON.\n";
            } else {
                std::cout << "Falha ao salvar usuário no JSON.\n";
            }
        } else if (option == 6) {
            std::string targetUser, newPass;
            std::cout << "Username (ou ENTER para seu próprio usuário): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, targetUser);
            if (targetUser.empty()) targetUser = auth_.currentUser();
            std::cout << "Nova senha: ";
            std::getline(std::cin, newPass);

            if (!auth_.canAccess("changePassword") && targetUser != auth_.currentUser()) {
                std::cout << "Acesso negado: você só pode alterar sua própria senha.\n";
                continue;
            }

            if (auth_.setPassword(targetUser, newPass)) {
                std::cout << "Senha atualizada e persistida no JSON.\n";
            } else {
                std::cout << "Falha ao atualizar senha.\n";
            }
        }
    }
}

}
