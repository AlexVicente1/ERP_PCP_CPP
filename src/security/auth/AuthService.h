#pragma once

#include <optional>
#include <string>
#include <unordered_set>

#include "../../domain/enums/Role.h"

namespace erp::pcp::security::auth {

class AuthService {
public:
    AuthService();

    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isAuthenticated() const;
    domain::enums::Role role() const;
    bool authorize(domain::enums::Role minimumRole) const;
    std::string currentUser() const;

    bool canAccess(const std::string& feature) const;
    bool setPassword(const std::string& username, const std::string& newPassword);
    bool addUser(const std::string& username, const std::string& password, const std::string& role);

private:
    static std::optional<std::string> resolveUsersFilePath();

    bool authenticated_{false};
    std::string currentUser_;
    domain::enums::Role currentRole_{domain::enums::Role::Operator};

    std::unordered_set<std::string> userFeatures_;
    std::string usersFilePath_;
};

}
