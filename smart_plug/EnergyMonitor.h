#ifndef ENERGYMONITOR_H
#define ENERGYMONITOR_H

#include <Arduino.h>

class EnergyMonitor {
  private:
    float totalEnergy;  // Total energy consumed in watt-hours
    unsigned long lastUpdateTime;  // The last time the power was updated

  public:
    // Constructor
    EnergyMonitor();

    // Update the energy consumed based on the current power
    void update(float currentPower);

    void reset();
    // Get the total energy consumed in watt-hours
    float getTotalEnergy() const;
};

#endif
