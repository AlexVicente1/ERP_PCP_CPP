#pragma once

#include <string>
#include <vector>

#include "../enums/Unit.h"
#include "../value_objects/ChemicalProperties.h"

namespace erp::pcp::domain::entities {

struct FormulaComponent {
    int rawMaterialId{0};
    double percentage{0.0};
};

struct FormulaRevision {
    int version{1};
    std::string responsibleTechnician;
    std::string revisionDate;
    std::vector<FormulaComponent> components;
};

class ChemicalProduct {
public:
    ChemicalProduct(int id, std::string code, std::string name, enums::Unit unit, double density);

    int id() const;
    const std::string& code() const;
    const std::string& name() const;
    enums::Unit unit() const;
    double density() const;
    double stock() const;
    double minimumStock() const;
    const value_objects::ChemicalProperties& properties() const;
    const std::vector<FormulaRevision>& formulaHistory() const;

    void setMinimumStock(double value);
    void setProperties(value_objects::ChemicalProperties properties);
    void addFormulaRevision(FormulaRevision revision);
    bool consume(double quantity);
    void addStock(double quantity);

private:
    int id_;
    std::string code_;
    std::string name_;
    enums::Unit unit_;
    double density_;
    double stock_{0.0};
    double minimumStock_{0.0};
    value_objects::ChemicalProperties properties_{};
    std::vector<FormulaRevision> formulaHistory_;
};

}
