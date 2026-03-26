#include "Logger.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace erp::pcp::infrastructure::logging {

namespace {
std::string now() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
}  // namespace

void Logger::info(const std::string& message) { std::cout << "[" << now() << "] [INFO] " << message << "\n"; }
void Logger::warn(const std::string& message) { std::cout << "[" << now() << "] [WARN] " << message << "\n"; }

}
