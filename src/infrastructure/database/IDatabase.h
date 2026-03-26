#pragma once

#include <string>

namespace erp::pcp::infrastructure::database {

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual bool connect(const std::string& connectionString) = 0;
    virtual void disconnect() = 0;
    virtual bool execute(const std::string& statement) = 0;
};

}
