#include "HallSensor.h"

// Constructor
HallSensor::HallSensor(int sensorPin) {
  pin = sensorPin;
  state = LOW;
  lastState = LOW;
  lastDebounceTime = 0;
  debounceDelay = 0;
  debounceEnabled = false;
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

  if (debounceEnabled) {
    if (reading != lastState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != state) {
        lastState = state;
        state = reading;
        handleStateChange();  // Handle the state change
      }
    }
  } else {
    if (reading != state) {
      lastState = state;
      state = reading;
      handleStateChange();  // Handle the state change
    }
  }
}

// Get the current state of the sensor
bool HallSensor::getState() const {
  return state;
}

// Attach a callback function for the click event (on press)
void HallSensor::onClick(void (*callback)()) {
  clickCallback = callback;
}

// Attach a callback function for the release event
void HallSensor::onRelease(void (*callback)()) {
  releaseCallback = callback;
}

// Internal method to handle state change
void HallSensor::handleStateChange() {
  if (lastState == LOW && state == HIGH && clickCallback != nullptr) {
    clickCallback();  // Call the click callback if the sensor is pressed
  } else if (lastState == HIGH && state == LOW && releaseCallback != nullptr) {
    releaseCallback();  // Call the release callback if the sensor is released
  }
}
