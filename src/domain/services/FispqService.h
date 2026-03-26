#pragma once

#include <string>

#include "../value_objects/ChemicalProperties.h"

namespace erp::pcp::domain::services {

class FispqService {
public:
    static std::string buildPdfReadyTemplate(const std::string& productName,
                                             const value_objects::ChemicalProperties& props);
};

}
