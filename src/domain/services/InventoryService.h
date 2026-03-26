#pragma once

namespace erp::pcp::domain::services {

class InventoryService {
public:
    static double convertMassToVolume(double massKg, double densityKgPerL);
    static double convertVolumeToMass(double liters, double densityKgPerL);
};

}
