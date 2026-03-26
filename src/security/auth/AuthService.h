#pragma once

#include <string>

#include "../../domain/enums/Role.h"

namespace erp::pcp::security::auth {

class AuthService {
public:
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isAuthenticated() const;
    domain::enums::Role role() const;
    bool authorize(domain::enums::Role minimumRole) const;
    std::string currentUser() const;

private:
    bool authenticated_{false};
    std::string currentUser_;
    domain::enums::Role currentRole_{domain::enums::Role::Operator};
};

}
