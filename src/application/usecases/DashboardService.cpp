#include "DashboardService.h"

#include <sstream>

namespace erp::pcp::application::usecases {

DashboardService::DashboardService(
    infrastructure::repositories::ChemicalProductRepository& productRepo,
    infrastructure::repositories::ProductionOrderRepository& orderRepo)
    : productRepo_(productRepo), orderRepo_(orderRepo) {}

std::string DashboardService::buildIndustrialKpiSummary() const {
    const auto products = productRepo_.findAll();
    const auto orders = orderRepo_.findAll();
    double totalEfficiency = 0.0;
    double totalWaste = 0.0;

    for (const auto& order : orders) {
        totalEfficiency += order.efficiency();
        totalWaste += order.losses();
    }

    const double avgEff = orders.empty() ? 0.0 : totalEfficiency / static_cast<double>(orders.size());

    std::ostringstream oss;
    oss << "Products: " << products.size() << " | Orders: " << orders.size()
        << " | Avg Efficiency: " << avgEff << "% | Waste: " << totalWaste << " kg";
    return oss.str();
}

}
