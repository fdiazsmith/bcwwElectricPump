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

    // Function pointers for the click and release events
    void (*clickCallback)() = nullptr;
    void (*releaseCallback)() = nullptr;

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

    // Attach a callback function for the click event (on press)
    void onClick(void (*callback)());

    // Attach a callback function for the release event
    void onRelease(void (*callback)());

  private:
    // Internal method to handle state change
    void handleStateChange();
};

#endif
