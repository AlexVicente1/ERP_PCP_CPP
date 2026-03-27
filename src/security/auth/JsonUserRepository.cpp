#include "JsonUserRepository.h"

#include <algorithm>
#include <fstream>

#include "../../../third_party/nlohmann/json.hpp"

namespace erp::pcp::security::auth {

using nlohmann::json;

JsonUserRepository::JsonUserRepository(std::string filePath) : filePath_(std::move(filePath)) {}

bool JsonUserRepository::load() {
    users_.clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) return false;

    json root;
    try {
        in >> root;
    } catch (...) {
        return false;
    }

    if (!root.is_object() || !root.contains("users") || !root["users"].is_array()) return false;

    for (const auto& item : root["users"]) {
        if (!item.is_object()) continue;
        User u;
        u.username = item.value("username", "");
        u.password = item.value("password", "");
        u.role = userRoleFromString(item.value("role", "User"));
        if (!u.username.empty()) users_.push_back(std::move(u));
    }

    return true;
}

bool JsonUserRepository::save() const {
    json root;
    root["users"] = json::array();

    for (const auto& u : users_) {
        root["users"].push_back({
            {"username", u.username},
            {"password", u.password},
            {"role", toString(u.role)}
        });
    }

    std::ofstream out(filePath_, std::ios::trunc);
    if (!out.is_open()) return false;

    out << root.dump(2);
    return true;
}

std::optional<User> JsonUserRepository::findByUsername(const std::string& username) const {
    auto it = std::find_if(users_.begin(), users_.end(),
                           [&](const User& u) { return u.username == username; });
    if (it == users_.end()) return std::nullopt;
    return *it;
}

bool JsonUserRepository::upsert(const User& user) {
    if (user.username.empty()) return false;

    auto it = std::find_if(users_.begin(), users_.end(),
                           [&](const User& u) { return u.username == user.username; });
    if (it == users_.end()) {
        users_.push_back(user);
    } else {
        *it = user;
    }
    return save();
}

bool JsonUserRepository::updatePassword(const std::string& username, const std::string& newPassword) {
    if (username.empty() || newPassword.empty()) return false;

    auto it = std::find_if(users_.begin(), users_.end(),
                           [&](const User& u) { return u.username == username; });
    if (it == users_.end()) return false;

    it->password = newPassword;
    return save();
}

}

