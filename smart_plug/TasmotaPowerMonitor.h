#ifndef TASMOTAPOWERMONITOR_H
#define TASMOTAPOWERMONITOR_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class TasmotaPowerMonitor {
  private:
    const char* ssid;
    const char* password;
    const char* tasmotaIP;

    // Helper method to send a command to the Tasmota device
    bool sendCommand(const String& command);

  public:
    // Constructor
    TasmotaPowerMonitor(const char* wifi_ssid, const char* wifi_password, const char* device_ip);

    // Initialize Wi-Fi connection
    void begin();

    // Method to get power consumption
    float getPowerConsumption();

    // Method to turn the switch on
    bool turnOn();

    // Method to turn the switch off
    bool turnOff();
};

#endif
