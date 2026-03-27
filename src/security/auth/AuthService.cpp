#include "AuthService.h"

#include <algorithm>
#include <cstdlib>
#include <filesystem>

#include "JsonUserRepository.h"
#include "UserRole.h"

namespace erp::pcp::security::auth {

namespace {
std::string normalizeFeature(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return value;
}
}

std::optional<std::string> AuthService::resolveUsersFilePath() {
    // 1) Permite apontar para qualquer arquivo em demo/local (sem versionar segredos)
    if (const char* env = std::getenv("ERP_PCP_USERS_FILE"); env && *env) {
        return std::string(env);
    }

    // 2) Caminho "privado" (ignorado pelo git)
    constexpr const char* privatePath = "data/private/users.json";
    if (std::filesystem::exists(privatePath)) return std::string(privatePath);

    // 3) Fallback versionado (modelo) — funciona para publicar o repo
    constexpr const char* demoPath = "data/demo/users.example.json";
    if (std::filesystem::exists(demoPath)) return std::string(demoPath);

    return std::nullopt;
}

AuthService::AuthService() {
    usersFilePath_ = resolveUsersFilePath().value_or("data/demo/users.example.json");
    userFeatures_ = {
        "viewdashboard",
        "createorder",
        "viewreports"
    };
}

bool AuthService::login(const std::string& username, const std::string& password) {
    JsonUserRepository repo(usersFilePath_);
    if (!repo.load()) return false;

    const auto found = repo.findByUsername(username);
    if (!found.has_value()) return false;
    if (found->password != password) return false;

    authenticated_ = true;
    currentUser_ = username;

    // Mantemos compatibilidade com o Role já existente no domínio.
    currentRole_ = (found->role == UserRole::Admin) ? domain::enums::Role::Administrator
                                                    : domain::enums::Role::Operator;
    return true;
}

void AuthService::logout() { authenticated_ = false; }
bool AuthService::isAuthenticated() const { return authenticated_; }
domain::enums::Role AuthService::role() const { return currentRole_; }
std::string AuthService::currentUser() const { return currentUser_; }
bool AuthService::authorize(domain::enums::Role minimumRole) const {
    return authenticated_ && static_cast<int>(currentRole_) >= static_cast<int>(minimumRole);
}

bool AuthService::canAccess(const std::string& feature) const {
    if (!authenticated_) return false;
    if (currentRole_ == domain::enums::Role::Administrator) return true;
    return userFeatures_.count(normalizeFeature(feature)) > 0;
}

bool AuthService::setPassword(const std::string& username, const std::string& newPassword) {
    JsonUserRepository repo(usersFilePath_);
    if (!repo.load()) return false;
    return repo.updatePassword(username, newPassword);
}

bool AuthService::addUser(const std::string& username, const std::string& password, const std::string& role) {
    JsonUserRepository repo(usersFilePath_);
    if (!repo.load()) return false;

    User u;
    u.username = username;
    u.password = password;
    u.role = userRoleFromString(role);
    return repo.upsert(u);
}

}
