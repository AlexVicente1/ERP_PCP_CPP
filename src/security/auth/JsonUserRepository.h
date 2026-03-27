#pragma once

#include <optional>
#include <string>
#include <vector>

#include "User.h"

namespace erp::pcp::security::auth {

class JsonUserRepository {
public:
    explicit JsonUserRepository(std::string filePath);

    bool load();
    bool save() const;

    std::optional<User> findByUsername(const std::string& username) const;
    bool upsert(const User& user);
    bool updatePassword(const std::string& username, const std::string& newPassword);

    const std::vector<User>& users() const { return users_; }

private:
    std::string filePath_;
    std::vector<User> users_;
};

}

