#pragma once

#include <string>
#include <vector>

namespace erp::pcp::domain::entities {

class BatchLot {
public:
    BatchLot(std::string lotCode, std::string manufactureDate, std::string expirationDate,
             std::string operatorName);

    const std::string& lotCode() const;
    const std::string& manufactureDate() const;
    const std::string& expirationDate() const;
    const std::string& operatorName() const;
    const std::vector<int>& rawMaterialTraceability() const;

    void addRawMaterialTrace(int rawMaterialId);

private:
    std::string lotCode_;
    std::string manufactureDate_;
    std::string expirationDate_;
    std::string operatorName_;
    std::vector<int> rawMaterialTraceability_;
};

}
