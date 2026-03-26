#include "ChemicalApiClient.h"

#include <unordered_map>

namespace erp::pcp::infrastructure::api {

domain::value_objects::ChemicalProperties ChemicalApiClient::fetchByName(
    const std::string& chemicalName) const {
    static const std::unordered_map<std::string, domain::value_objects::ChemicalProperties> db = {
        {"acetone", {"C3H6O", "58.08", "Flammable liquid", "CID:180"}},
        {"ethanol", {"C2H6O", "46.07", "Highly flammable", "CID:702"}},
        {"methanol", {"CH4O", "32.042", "Toxic by ingestion", "CID:887"}},
        {"benzene", {"C6H6", "78.11", "Carcinogenic exposure risk", "CID:241"}},
        {"toluene", {"C7H8", "92.14", "Flammable vapor", "CID:1140"}}};

    const auto it = db.find(chemicalName);
    if (it != db.end()) return it->second;
    return {"N/A", "N/A", "Check external FISPQ", "N/A"};
}

}
