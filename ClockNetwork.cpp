#include "ClockNetwork.hpp"

#include <ESP8266WiFi.h>

void ClockNetwork::start_wifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(F("Connected to ")); Serial.println(ssid);
  Serial.print(F("IP address: "));  Serial.println(WiFi.localIP());
  Serial.println(F("Setup done"));
}
