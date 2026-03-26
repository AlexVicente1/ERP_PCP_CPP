#include "BatchLot.h"

namespace erp::pcp::domain::entities {

BatchLot::BatchLot(std::string lotCode, std::string manufactureDate, std::string expirationDate,
                   std::string operatorName)
    : lotCode_(std::move(lotCode)),
      manufactureDate_(std::move(manufactureDate)),
      expirationDate_(std::move(expirationDate)),
      operatorName_(std::move(operatorName)) {}

const std::string& BatchLot::lotCode() const { return lotCode_; }
const std::string& BatchLot::manufactureDate() const { return manufactureDate_; }
const std::string& BatchLot::expirationDate() const { return expirationDate_; }
const std::string& BatchLot::operatorName() const { return operatorName_; }
const std::vector<int>& BatchLot::rawMaterialTraceability() const { return rawMaterialTraceability_; }
void BatchLot::addRawMaterialTrace(int rawMaterialId) { rawMaterialTraceability_.push_back(rawMaterialId); }

}
