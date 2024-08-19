#include "HallSensor.h"

// Constructor
HallSensor::HallSensor(int sensorPin) {
  pin = sensorPin;
  state = LOW;
  lastState = LOW;
  lastDebounceTime = 0;
  debounceDelay = 0;
  debounceEnabled = false;
  stateChangedFlag = false;
}

// Initialize the sensor
void HallSensor::begin() {
  pinMode(pin, INPUT);
}

// Enable debounce and set the debounce delay
void HallSensor::useDebounce(unsigned long debounceTime) {
  debounceDelay = debounceTime;
  debounceEnabled = true;
}

// Update the sensor state (must be called in loop)
void HallSensor::update() {
  int reading = digitalRead(pin);
  stateChangedFlag = false;  // Reset the stateChanged flag

  if (debounceEnabled) {
    if (reading != lastState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != state) {
        state = reading;
        stateChangedFlag = true;  // State has changed
      }
    }
  } else {
    if (reading != state) {
      state = reading;
      stateChangedFlag = true;  // State has changed
    }
  }

  lastState = state;
}

// Get the current state of the sensor
bool HallSensor::getState() const {
  return state;
}

// Check if the sensor state has changed
bool HallSensor::stateChanged() {
  return stateChangedFlag;
}
