#include "InventoryService.h"

namespace erp::pcp::domain::services {

double InventoryService::convertMassToVolume(double massKg, double densityKgPerL) {
    if (densityKgPerL <= 0.0) return 0.0;
    return massKg / densityKgPerL;
}

double InventoryService::convertVolumeToMass(double liters, double densityKgPerL) {
    return liters * densityKgPerL;
}

}
