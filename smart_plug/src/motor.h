#pragma once

#include <AccelStepper.h>

class Motor {
  AccelStepper stepper;
  bool isRunning = false;
  int enablePin;

public:
  Motor(int pin_dir, int pin_step, int pin_enable)
      : stepper(AccelStepper::DRIVER, pin_step, pin_dir), enablePin(pin_enable) {}

  void begin() {
    pinMode(enablePin, OUTPUT);
    disableMotor();  // Disable the motor by default
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(50);
  }

  void enableMotor() {
    digitalWrite(enablePin, LOW);  // Assuming LOW enables the motor driver
  }

  void disableMotor() {
    digitalWrite(enablePin, HIGH);  // Assuming HIGH disables the motor driver
  }
  bool running() { return isRunning; }
  
  void running(bool value) {
    isRunning = value;
    Serial.printf("Motor: %s\r\n", isRunning ? "Running" : "Not running");
    // if(isRunning) {
    //   enableMotor();
    // } else {
    //   disableMotor();
    // }
  }

  void update() {
    if (isRunning) {
      stepper.runSpeed();
    }
  }
};