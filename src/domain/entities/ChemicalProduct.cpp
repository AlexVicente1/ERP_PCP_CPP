#include "ChemicalProduct.h"

namespace erp::pcp::domain::entities {

ChemicalProduct::ChemicalProduct(int id, std::string code, std::string name, enums::Unit unit,
                                 double density)
    : id_(id), code_(std::move(code)), name_(std::move(name)), unit_(unit), density_(density) {}

int ChemicalProduct::id() const { return id_; }
const std::string& ChemicalProduct::code() const { return code_; }
const std::string& ChemicalProduct::name() const { return name_; }
enums::Unit ChemicalProduct::unit() const { return unit_; }
double ChemicalProduct::density() const { return density_; }
double ChemicalProduct::stock() const { return stock_; }
double ChemicalProduct::minimumStock() const { return minimumStock_; }
const value_objects::ChemicalProperties& ChemicalProduct::properties() const { return properties_; }
const std::vector<FormulaRevision>& ChemicalProduct::formulaHistory() const { return formulaHistory_; }

void ChemicalProduct::setMinimumStock(double value) { minimumStock_ = value; }
void ChemicalProduct::setProperties(value_objects::ChemicalProperties properties) {
    properties_ = std::move(properties);
}
void ChemicalProduct::addFormulaRevision(FormulaRevision revision) {
    formulaHistory_.push_back(std::move(revision));
}
bool ChemicalProduct::consume(double quantity) {
    if (quantity <= 0.0 || quantity > stock_) return false;
    stock_ -= quantity;
    return true;
}
void ChemicalProduct::addStock(double quantity) {
    if (quantity > 0.0) stock_ += quantity;
}

}
