#pragma once

#include <stdexcept>
#include <string>

namespace erp::pcp::shared::exceptions {

class DomainException : public std::runtime_error {
public:
    explicit DomainException(const std::string& message) : std::runtime_error(message) {}
};

}
