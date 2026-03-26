#pragma once

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace erp::pcp::shared::utils {

inline std::string now() {
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

}
