#include "QualityInspection.h"

namespace erp::pcp::domain::entities {

QualityInspection::QualityInspection(double ph, double density, double viscosity, bool approved)
    : ph_(ph), density_(density), viscosity_(viscosity), approved_(approved) {}

double QualityInspection::ph() const { return ph_; }
double QualityInspection::density() const { return density_; }
double QualityInspection::viscosity() const { return viscosity_; }
bool QualityInspection::approved() const { return approved_; }

}
