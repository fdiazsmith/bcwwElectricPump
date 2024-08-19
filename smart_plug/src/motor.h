#pragma once

#include <AccelStepper.h>

class Motor {
  AccelStepper stepper;
  bool isRunning = false;

public:
  Motor(int pin_dir, int pin_step)
      : stepper(AccelStepper::DRIVER, pin_step, pin_dir) {}

  void begin() {
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(50);
  }

  bool running() { return isRunning; }
  void running(bool value) {
    isRunning = value;
    Serial.printf("Motor: %s\r\n", isRunning ? "Running" : "Not running");
  }

  void update() {
    if (isRunning) {
      stepper.runSpeed();
    }
  }
};