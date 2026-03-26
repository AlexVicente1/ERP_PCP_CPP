#include "AuthService.h"

namespace erp::pcp::security::auth {

bool AuthService::login(const std::string& username, const std::string& password) {
    if (username == "admin" && password == "pcp123") {
        authenticated_ = true;
        currentUser_ = username;
        currentRole_ = domain::enums::Role::Administrator;
        return true;
    }
    if (username == "engineer" && password == "pcp123") {
        authenticated_ = true;
        currentUser_ = username;
        currentRole_ = domain::enums::Role::ChemicalEngineer;
        return true;
    }
    return false;
}

void AuthService::logout() { authenticated_ = false; }
bool AuthService::isAuthenticated() const { return authenticated_; }
domain::enums::Role AuthService::role() const { return currentRole_; }
std::string AuthService::currentUser() const { return currentUser_; }
bool AuthService::authorize(domain::enums::Role minimumRole) const {
    return authenticated_ && static_cast<int>(currentRole_) >= static_cast<int>(minimumRole);
}

}
