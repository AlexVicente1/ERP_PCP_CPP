#pragma once

#include "../../domain/enums/Unit.h"
#include "../../infrastructure/api/ChemicalApiClient.h"
#include "../../infrastructure/repositories/ChemicalProductRepository.h"
#include "../../security/audit/AuditLogger.h"
#include "../dto/ChemicalProductDto.h"

namespace erp::pcp::application::usecases {

class RegisterChemicalProductUseCase {
public:
    RegisterChemicalProductUseCase(infrastructure::repositories::ChemicalProductRepository& repo,
                                   infrastructure::api::ChemicalApiClient& api,
                                   security::audit::AuditLogger& audit);

    void execute(const dto::ChemicalProductDto& input, const std::string& user);

private:
    infrastructure::repositories::ChemicalProductRepository& repo_;
    infrastructure::api::ChemicalApiClient& api_;
    security::audit::AuditLogger& audit_;
};

}
