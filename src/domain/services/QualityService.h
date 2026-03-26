#pragma once

#include "../entities/QualityInspection.h"

namespace erp::pcp::domain::services {

class QualityService {
public:
    static bool approveBatch(const entities::QualityInspection& inspection);
};

}
