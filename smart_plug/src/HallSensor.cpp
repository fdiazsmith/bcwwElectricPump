#include "HallSensor.h"

// Constructor with activeState parameter
HallSensor::HallSensor(int sensorPin, bool activeState) {
  pin = sensorPin;
  state = !activeState;  // Initialize state to the opposite of the active state
  lastState = !activeState;  // Same for lastState
  lastDebounceTime = 0;
  debounceDelay = 0;
  debounceEnabled = false;
  this->activeState = activeState;  // Store the active state
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
  if (lastState != state) {
    if (state == activeState && clickCallback != nullptr) {
      clickCallback();  // Call the click callback if the sensor is in active state
    } else if (state != activeState && releaseCallback != nullptr) {
      releaseCallback();  // Call the release callback if the sensor is in inactive state
    }
  }
}
