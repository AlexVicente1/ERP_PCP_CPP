#pragma once

#include "IDatabase.h"

namespace erp::pcp::infrastructure::database {

class SQLiteReadyDatabase : public IDatabase {
public:
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    bool execute(const std::string& statement) override;

private:
    bool connected_{false};
};

}
