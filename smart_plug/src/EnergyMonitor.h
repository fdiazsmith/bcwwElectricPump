#ifndef ENERGYMONITOR_H
#define ENERGYMONITOR_H

#include <Arduino.h>

class EnergyMonitor {
  private:
    float totalEnergy;  // Total energy consumed in watt-hours
    unsigned long lastUpdateTime;  // The last time the power was updated
    void (*thresholdCallback)() = nullptr;  // Callback function for threshold crossing
    float lastQuantizedEnergy;  // Tracks the last quantized energy value
    float quantizationThreshold;  // Quantization threshold (e.g., 0.1, 0.01, 0.5, etc.)

  public:
    // Constructor
    EnergyMonitor();

    // Update the energy consumed based on the current power
    void update(float currentPower);

    // Reset the energy monitor
    void reset();

    // Set the quantization threshold
    void setQuantizationThreshold(float threshold);

    // Attach a callback function for when the energy threshold is crossed
    void setThresholdCallback(void (*callback)());

    // Get the total energy consumed in watt-hours
    float getTotalEnergy() const;

  private:
    // Method to call when a power threshold is crossed
    void powerTick();
};

#endif
