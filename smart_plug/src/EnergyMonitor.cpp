#include "EnergyMonitor.h"

// Constructor
EnergyMonitor::EnergyMonitor() {
  totalEnergy = 0.0;
  lastUpdateTime = millis();
  lastQuantizedEnergy = 0.0;  // Initialize the last quantized energy
  quantizationThreshold = 0.1;  // Default quantization threshold
}

// Update the energy consumed based on the current power
void EnergyMonitor::update(float currentPower) {
  unsigned long currentTime = millis();
  float elapsedTimeHours = (currentTime - lastUpdateTime) / 3600000.0;  // Convert milliseconds to hours
  totalEnergy += currentPower * elapsedTimeHours;  // Increment total energy in Wh
  lastUpdateTime = currentTime;

  float quantizedEnergy = floor(totalEnergy / quantizationThreshold) * quantizationThreshold;  // Quantize energy to the specified threshold

  // Check if the quantized energy has crossed the next threshold mark
  if (quantizedEnergy != lastQuantizedEnergy) {
    Serial.println("\tThreshold crossed at: " + String(quantizedEnergy) + " Wh");
    lastQuantizedEnergy = quantizedEnergy;
    powerTick();  // Call the threshold callback if set
  }
}

// Reset the energy monitor
void EnergyMonitor::reset() {
  totalEnergy = 0.0;
  lastUpdateTime = millis();
  lastQuantizedEnergy = 0.0;  // Reset quantized energy tracking
  Serial.println("Energy Monitor Reset");
}

// Set the quantization threshold
void EnergyMonitor::setQuantizationThreshold(float threshold) {
  quantizationThreshold = threshold;
}

// Attach a callback function for when the energy threshold is crossed
void EnergyMonitor::setThresholdCallback(void (*callback)()) {
  thresholdCallback = callback;
}

// Method to call when a power threshold is crossed
void EnergyMonitor::powerTick() {
  if (thresholdCallback != nullptr) {
    thresholdCallback();  // Call the attached callback function
  }
}

// Get the total energy consumed in watt-hours
float EnergyMonitor::getTotalEnergy() const {
  return totalEnergy;
}
