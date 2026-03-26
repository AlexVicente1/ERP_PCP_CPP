#pragma once

#include <string>

namespace erp::pcp::infrastructure::logging {

class Logger {
public:
    static void info(const std::string& message);
    static void warn(const std::string& message);
};

}
