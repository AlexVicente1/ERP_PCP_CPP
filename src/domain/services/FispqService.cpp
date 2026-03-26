#include "FispqService.h"

#include <sstream>

namespace erp::pcp::domain::services {

std::string FispqService::buildPdfReadyTemplate(const std::string& productName,
                                                const value_objects::ChemicalProperties& props) {
    std::ostringstream out;
    out << "FISPQ - " << productName << "\n"
        << "Identifier: " << props.identifier << "\n"
        << "Formula: " << props.molecularFormula << "\n"
        << "Molecular Weight: " << props.molecularWeight << "\n"
        << "Hazard: " << props.hazardInfo << "\n"
        << "PPE: Chemical gloves, goggles, face shield\n"
        << "Storage: Dry, ventilated, segregated storage\n"
        << "Toxicity: Refer to complete toxicology sheet";
    return out.str();
}

}
