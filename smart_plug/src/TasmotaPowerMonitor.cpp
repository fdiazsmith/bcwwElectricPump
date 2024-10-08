#include "TasmotaPowerMonitor.h"

// Constructor
TasmotaPowerMonitor::TasmotaPowerMonitor(const char *wifi_ssid,
                                         const char *wifi_password,
                                         const char *device_ip) {
  ssid = wifi_ssid;
  password = wifi_password;
  tasmotaIP = device_ip;
}

// Initialize Wi-Fi connection
void TasmotaPowerMonitor::begin() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// Method to get power consumption
float TasmotaPowerMonitor::getPowerConsumption() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String url = String("http://") + tasmotaIP + "/cm?cmnd=Status%208";

    http.begin(client, url);
    int httpCode = http.GET();
    float power = -1.0; // Default to -1.0 if unable to retrieve power

    if (httpCode > 0) {
      String payload = http.getString();
      // Serial.println("Received payload: " + payload);

      // Parse JSON to extract power consumption value
      StaticJsonDocument<1024> jsonBuffer;
      DeserializationError error = deserializeJson(jsonBuffer, payload);

      if (!error) {
        power = jsonBuffer["StatusSNS"]["ENERGY"]["Power"];
        Serial.print("Tasmota: Power Consumption: ");
        Serial.print(power);
        Serial.println(" W");
      } else {
        Serial.println("JSON parsing failed");
      }
    } else {
      Serial.println("Error in HTTP request");
    }
    http.end();
    return power;
  } else {
    Serial.println("WiFi not connected");
    return -1.0; // Return -1.0 if not connected to Wi-Fi
  }
}

// Helper method to send a command to the Tasmota device
bool TasmotaPowerMonitor::sendCommand(const String &command) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String url = String("http://") + tasmotaIP + "/cm?cmnd=" + command;

    http.begin(client, url);
    int httpCode = http.GET();
    http.end();

    return (httpCode == HTTP_CODE_OK);
  } else {
    Serial.println("WiFi not connected");
    return false;
  }
}

// Method to turn the switch on
bool TasmotaPowerMonitor::turnOn() { return sendCommand("Power%20On"); }

// Method to turn the switch off
bool TasmotaPowerMonitor::turnOff() { return sendCommand("Power%20Off"); }
