#pragma once

#include <string>

namespace erp::pcp::application::dto {

struct ChemicalProductDto {
    int id{0};
    std::string code;
    std::string name;
    std::string apiLookupName;
    double density{1.0};
    double initialStock{0.0};
    double minimumStock{0.0};
};

}
