#pragma once

#include <AccelStepper.h>

class Motor {
  AccelStepper stepper;
  int enablePin;            // Pin to enable or disable the motor driver
  bool isRunning = false;
  int stepIncrement = 100;  // Default step increment value

public:
  // Constructor with enable pin
  Motor(int pin_dir, int pin_step, int pin_enable)
      : stepper(AccelStepper::DRIVER, pin_step, pin_dir), enablePin(pin_enable) {}

  void begin() {
    pinMode(enablePin, OUTPUT);
    disableMotor();  // Disable the motor by default

    stepper.setMaxSpeed(9000);
    stepper.setAcceleration(1000);
    stepper.setSpeed(950);
  }

  void enableMotor() {
    digitalWrite(enablePin, LOW);  // Assuming LOW enables the motor driver
  }

  void disableMotor() {
    digitalWrite(enablePin, HIGH);  // Assuming HIGH disables the motor driver
  }

  void update() {
    if (isRunning) {
      if (stepper.distanceToGo() == 0) {
        isRunning = false;  // Stop the motor when the position is reached
        disableMotor();     // Disable the motor driver
        Serial.println("Motor: Not running");
      } else {
        stepper.run();
      }
    }
  }

  // Set the direction of the motor: true for forward, false for reverse
  void setDir(bool forward) {
    stepper.setSpeed(forward ? abs(stepper.speed()) : -abs(stepper.speed()));
    stepper.setMaxSpeed(forward ? abs(stepper.maxSpeed()) : -abs(stepper.maxSpeed()));
    stepIncrement = forward ? abs(stepIncrement) : -abs(stepIncrement);
  }

  // Increment the motor by the current step increment (non-blocking)
  void incrementPower() {
    enableMotor();      // Enable the motor driver
    stepper.move(stepIncrement);
    isRunning = true;
    Serial.println("Motor: Running");
  }

  // Set the number of steps to move when incrementPower is called
  void setPowerIncrement(int steps) {
    stepIncrement = steps;
  }

  // Set the speed of the motor (steps per second)
  void setSpeed(float speed) {
    int dir = stepper.speed() > 0 ? 1 : -1;
    stepper.setSpeed(speed * dir);
  }

  // Check if the motor is currently running
  bool isMotorRunning() const {
    return isRunning;
  }
};
