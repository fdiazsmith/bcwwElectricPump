


#include "TasmotaPowerMonitor.h"
#include "EnergyMonitor.h"
#include "HallSensor.h"

// Instantiate the TasmotaPowerMonitor class
TasmotaPowerMonitor tasmotaMonitor("Solar Eclipse", "baodoubletime", "192.168.4.29");
EnergyMonitor energyMonitor;
HallSensor hallSensor(25);  // Hall sensor on pin 13 with 50ms debounce time

long lastUpdateTime = 0;

void setup() {
  
  Serial.begin(115200);
  Serial.println("BCWW - Gas Pump");
  tasmotaMonitor.begin();
  hallSensor.begin();
  

}


void loop() {

  hallSensor.update();
  if (hallSensor.stateChanged()) {
    if (hallSensor.getState() == LOW) {
      Serial.println("button state LOW");
      energyMonitor.reset();
      if (tasmotaMonitor.turnOff()) {
        Serial.println("Switch turned off");
      } else {
        Serial.println("Failed to turn off the switch");
      }
    }
    else{
      if (tasmotaMonitor.turnOn()) {
        Serial.println("Switch turned on");
      } else {
        Serial.println("Failed to turn on the switch");
      }
    }
  }

  if( lastUpdateTime == 0 || millis() - lastUpdateTime > 10000){
    lastUpdateTime = millis();
    Serial.println("Updating");

    float power = tasmotaMonitor.getPowerConsumption();
    energyMonitor.update(power);
   
    

    Serial.print("Current Power: ");
    Serial.print(power);
    Serial.println(" W");

    Serial.print("Total Energy Consumed: ");
    Serial.print(energyMonitor.getTotalEnergy());
    Serial.println(" Wh");
  }
 

 
 
}
