#pragma once

#include <string>

namespace erp::pcp::domain::value_objects {

struct ChemicalProperties {
    std::string molecularFormula;
    std::string molecularWeight;
    std::string hazardInfo;
    std::string identifier;
};

}
