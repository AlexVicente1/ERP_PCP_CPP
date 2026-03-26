#include "RegisterChemicalProductUseCase.h"

#include "../../domain/entities/ChemicalProduct.h"
#include "../../shared/utils/DateTime.h"

namespace erp::pcp::application::usecases {

RegisterChemicalProductUseCase::RegisterChemicalProductUseCase(
    infrastructure::repositories::ChemicalProductRepository& repo,
    infrastructure::api::ChemicalApiClient& api, security::audit::AuditLogger& audit)
    : repo_(repo), api_(api), audit_(audit) {}

void RegisterChemicalProductUseCase::execute(const dto::ChemicalProductDto& input,
                                             const std::string& user) {
    domain::entities::ChemicalProduct product(input.id, input.code, input.name, domain::enums::Unit::Kg,
                                              input.density);
    product.setMinimumStock(input.minimumStock);
    product.addStock(input.initialStock);
    product.setProperties(api_.fetchByName(input.apiLookupName));

    domain::entities::FormulaRevision rev;
    rev.version = 1;
    rev.responsibleTechnician = user;
    rev.revisionDate = shared::utils::now();
    product.addFormulaRevision(rev);

    repo_.save(std::move(product));
    audit_.record(user, "Created chemical product " + input.code, shared::utils::now());
}

}
