#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace erp::pcp::utils {

class Logger {
public:
    static void info(const std::string& message) { log("INFO", message); }
    static void error(const std::string& message) { log("ERROR", message); }

private:
    static void log(const std::string& level, const std::string& message) {
        std::cout << "[" << timestamp() << "]"
                  << " [" << level << "] " << message << '\n';
    }

    static std::string timestamp() {
        const auto now = std::chrono::system_clock::now();
        const std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &timeNow);
#else
        localtime_r(&timeNow, &localTime);
#endif
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};

}  // namespace erp::pcp::utils
