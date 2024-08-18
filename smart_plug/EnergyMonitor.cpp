#include "EnergyMonitor.h"

// Constructor
EnergyMonitor::EnergyMonitor() {
  totalEnergy = 0.0;
  lastUpdateTime = millis();
}

// Update the energy consumed based on the current power
void EnergyMonitor::update(float currentPower) {
  unsigned long currentTime = millis();
  float elapsedTimeHours = (currentTime - lastUpdateTime) / 3600000.0;  // Convert milliseconds to hours
  totalEnergy += currentPower * elapsedTimeHours;  // Increment total energy in Wh
  lastUpdateTime = currentTime;
}

void EnergyMonitor::reset() {
  totalEnergy = 0.0;
  lastUpdateTime = millis();
}

// Get the total energy consumed in watt-hours
float EnergyMonitor::getTotalEnergy() const {
  return totalEnergy;
}
