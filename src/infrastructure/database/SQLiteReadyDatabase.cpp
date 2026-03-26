#include "SQLiteReadyDatabase.h"

#include "../logging/Logger.h"

namespace erp::pcp::infrastructure::database {

bool SQLiteReadyDatabase::connect(const std::string& connectionString) {
    connected_ = true;
    logging::Logger::info("Database connected (SQLite-ready): " + connectionString);
    return true;
}

void SQLiteReadyDatabase::disconnect() {
    connected_ = false;
    logging::Logger::info("Database disconnected.");
}

bool SQLiteReadyDatabase::execute(const std::string& statement) {
    if (!connected_) return false;
    logging::Logger::info("SQL> " + statement);
    return true;
}

}
