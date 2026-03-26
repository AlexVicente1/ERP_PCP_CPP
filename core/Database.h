#pragma once

#include <string>

namespace erp::pcp::core {

class Database {
public:
    explicit Database(std::string connectionString);
    ~Database() = default;

    bool connect();
    void disconnect();
    bool isConnected() const;

    bool executeQuery(const std::string& query) const;

private:
    std::string connectionString_;
    bool connected_{false};
};

}  // namespace erp::pcp::core
