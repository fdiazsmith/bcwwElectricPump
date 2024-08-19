#ifndef HALLSENSOR_H
#define HALLSENSOR_H

#include <Arduino.h>

class HallSensor {
  private:
    int pin;  // Pin connected to the hall sensor or button
    bool state;  // Current state of the sensor (pressed/released)
    bool lastState;  // Last known state of the sensor
    unsigned long lastDebounceTime;  // Time the sensor state last changed
    unsigned long debounceDelay;  // Debounce delay in milliseconds
    bool debounceEnabled;  // Flag to indicate if debounce is enabled
    bool stateChangedFlag;  // Flag to indicate if the state has changed

  public:
    // Constructor
    HallSensor(int sensorPin);

    // Initialize the sensor
    void begin();

    // Update the sensor state (must be called in loop)
    void update();

    // Get the current state of the sensor
    bool getState() const;

    // Check if the sensor state has changed
    bool stateChanged();

    // Enable debounce and set the debounce delay
    void useDebounce(unsigned long debounceTime);
};

#endif
