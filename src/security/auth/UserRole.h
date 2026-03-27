#pragma once

#include <string>

namespace erp::pcp::security::auth {

enum class UserRole { User, Admin };

inline std::string toString(UserRole role) {
    switch (role) {
        case UserRole::Admin: return "Admin";
        case UserRole::User: return "User";
    }
    return "User";
}

inline UserRole userRoleFromString(const std::string& value) {
    if (value == "Admin" || value == "admin") return UserRole::Admin;
    return UserRole::User;
}

}

