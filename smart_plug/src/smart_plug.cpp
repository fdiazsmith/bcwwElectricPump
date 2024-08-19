

#include "EnergyMonitor.h"
#include "HallSensor.h"
#include "TasmotaPowerMonitor.h"
#include "motor.h"
#include "pins.h"

#include <OneButton.h>

// Instantiate the TasmotaPowerMonitor class
TasmotaPowerMonitor tasmotaMonitor("Solar Eclipse", "baodoubletime",
                                   "192.168.4.29");
EnergyMonitor energyMonitor;
HallSensor hallSensor(
    PIN_HALL_SENSOR1); // Hall sensor on pin 13 with 50ms debounce time

Motor motor(PIN_MOTOR_DIR, PIN_MOTOR_STEP);

OneButton button(PIN_BUTTON, true);

void httpTask(void *pvParameters) {
  while (true) {
    Serial.println("Updating");

    float power = tasmotaMonitor.getPowerConsumption();
    energyMonitor.update(power);

    Serial.print("Current Power: ");
    Serial.print(power);
    Serial.println(" W");

    Serial.print("Total Energy Consumed: ");
    Serial.print(energyMonitor.getTotalEnergy());
    Serial.println(" Wh");

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void setup() {

  Serial.begin(115200);
  Serial.println("BCWW - Gas Pump");
  tasmotaMonitor.begin();
  hallSensor.begin();
  motor.begin();

  button.attachClick([]() { motor.running(!motor.running()); });
  button.setup(PIN_BUTTON);

  // create task for the http stuff
  xTaskCreate(httpTask,   /* Function to implement the task */
              "httpTask", /* Name of the task */
              10000,      /* Stack size in words */
              NULL,       /* Task input parameter */
              1,          /* Priority of the task */
              NULL);
}

void loop() {

  hallSensor.update();
  // if (hallSensor.stateChanged()) {
  //   if (hallSensor.getState() == LOW) {
  //     Serial.println("button state LOW");
  //     energyMonitor.reset();
  //     if (tasmotaMonitor.turnOff()) {
  //       Serial.println("Switch turned off");
  //     } else {
  //       Serial.println("Failed to turn off the switch");
  //     }
  //   } else {
  //     if (tasmotaMonitor.turnOn()) {
  //       Serial.println("Switch turned on");
  //     } else {
  //       Serial.println("Failed to turn on the switch");
  //     }
  //   }
  // }

  button.tick();
  motor.update();
}
