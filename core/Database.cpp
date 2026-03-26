#include "Database.h"

#include <iostream>

namespace erp::pcp::core {

Database::Database(std::string connectionString)
    : connectionString_(std::move(connectionString)) {}

bool Database::connect() {
    connected_ = true;
    std::cout << "[Database] Connected to: " << connectionString_ << '\n';
    return connected_;
}

void Database::disconnect() {
    connected_ = false;
    std::cout << "[Database] Connection closed.\n";
}

bool Database::isConnected() const { return connected_; }

bool Database::executeQuery(const std::string& query) const {
    if (!connected_) {
        std::cout << "[Database] Query skipped. Not connected.\n";
        return false;
    }

    std::cout << "[Database] Executing query: " << query << '\n';
    return true;
}

}  // namespace erp::pcp::core
