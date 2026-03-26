#include "QualityService.h"

namespace erp::pcp::domain::services {

bool QualityService::approveBatch(const entities::QualityInspection& inspection) {
    const bool phOk = inspection.ph() >= 6.0 && inspection.ph() <= 8.0;
    const bool densityOk = inspection.density() > 0.7 && inspection.density() < 2.0;
    const bool viscosityOk = inspection.viscosity() > 10.0;
    return inspection.approved() && phOk && densityOk && viscosityOk;
}

}
