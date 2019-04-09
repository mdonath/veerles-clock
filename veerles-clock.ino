#include "Clock.hpp"

#include "credentials.h"
#ifndef SSID_NAME
#error You must configure SSID_NAME in credentials.h
#endif
#ifndef SSID_PASSWORD
#error You must configure SSID_PASSWORD in credentials.h
#endif

#ifndef NTP_ADDRESS
#define NTP_ADDRESS "nl.ntp.pool.org"
#endif

Clock my_clock;

void onPressed(uint8_t pin, bool heldDown) {
  clock_button_t button = static_cast<clock_button_t>(pin);
  my_clock.event_button_pressed(button, heldDown);
}

void onTimer() {
  my_clock.tick();
}

void setup() {
  Serial.begin(115200);

  my_clock.begin(D5, D6, onPressed, SSID_NAME, SSID_PASSWORD, NTP_ADDRESS);

  taskManager.scheduleFixedRate(100, onTimer);
}

void loop() {
  taskManager.runLoop();
}
