#pragma once

#include <string>
#include <vector>

namespace erp::pcp::security::audit {

class AuditLogger {
public:
    void record(const std::string& user, const std::string& action, const std::string& timestamp);
    const std::vector<std::string>& entries() const;

private:
    std::vector<std::string> entries_;
};

}
