#include "AuditLogger.h"

namespace erp::pcp::security::audit {

void AuditLogger::record(const std::string& user, const std::string& action,
                         const std::string& timestamp) {
    entries_.push_back(timestamp + " | " + user + " | " + action);
}
const std::vector<std::string>& AuditLogger::entries() const { return entries_; }

}
