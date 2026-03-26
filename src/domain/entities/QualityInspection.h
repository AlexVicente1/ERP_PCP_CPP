#pragma once

namespace erp::pcp::domain::entities {

class QualityInspection {
public:
    QualityInspection(double ph, double density, double viscosity, bool approved);

    double ph() const;
    double density() const;
    double viscosity() const;
    bool approved() const;

private:
    double ph_;
    double density_;
    double viscosity_;
    bool approved_;
};

}
