#pragma once

#include <string>

#include "../../domain/value_objects/ChemicalProperties.h"

namespace erp::pcp::infrastructure::api {

class ChemicalApiClient {
public:
    domain::value_objects::ChemicalProperties fetchByName(const std::string& chemicalName) const;
};

}
