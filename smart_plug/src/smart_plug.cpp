

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
HallSensor pumpEngaged(PIN_HALL_SENSOR1, LOW); // Hall sensor for pump engaged
HallSensor resetPump(PIN_HALL_SENSOR2, LOW); // Hall sensor for pump engaged

Motor motor(PIN_MOTOR_DIR, PIN_MOTOR_STEP, PIN_MOTOR_ENABLE);

OneButton button(PIN_BUTTON, true);

void httpTask(void *pvParameters) {
  while (true) {
    // Serial.println("Updating");
    if(pumpEngaged.getState() == pumpEngaged.activeState) {
      float power = tasmotaMonitor.getPowerConsumption();
      energyMonitor.update(power);
    
    }
    else{
      Serial.print("/");
    }
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}
// Function to be called on click (press)
void onPumpEngagedClick() {
  Serial.println("Pump engaged!");
  // motor.enableMotor();
  tasmotaMonitor.turnOn();
  motor.running(true);
  
}

// Function to be called on release
void onPumpEngagedRelease() {
  Serial.println("Pump released!");
  // motor.disableMotor();
  tasmotaMonitor.turnOff();
    motor.running(false);
}


void setup() {

  Serial.begin(115200);
  Serial.println("BCWW - Gas Pump");
  // Set the callback function for energy threshold crossing
  // energyMonitor.setThresholdCallback([]() { motor.incrementPower(); });

  // Set the quantization threshold to 0.1 Wh
  energyMonitor.setQuantizationThreshold(0.1);

  // TASMOTA SMART PLUG
  tasmotaMonitor.begin();

  // HALL SENSORS
  pumpEngaged.begin();
   // Attach the onPumpEngagedClick function to the sensor's click event
  pumpEngaged.onClick(onPumpEngagedClick);
  // Attach the onPumpEngagedRelease function to the sensor's release event
  pumpEngaged.onRelease(onPumpEngagedRelease);
  resetPump.begin();
  // Attach the onResetPumpClick function to the sensor's click event
  resetPump.onClick([]() { energyMonitor.reset(); });

  
  //MOTOR
  // motor.begin();
  // motor.setSpeed(200);          // Set the motor speed to 200 steps per second
  // motor.setPowerIncrement(400);  // Set the increment to 400 steps to move 1/10 of a rotation
  // motor.setDir(true);           // Set the direction to forward
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

  pumpEngaged.update();
  resetPump.update();
  motor.update();
 

}
