#pragma once

#include <string>

#include "UserRole.h"

namespace erp::pcp::security::auth {

struct User {
    std::string username;
    std::string password;
    UserRole role{UserRole::User};
};

}

