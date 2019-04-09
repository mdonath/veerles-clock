#include "Clock.hpp"

void Clock::begin(int tx, int rx, KeyCallbackFn callback, const char* ssid, const char* password, const char* ntp_server) {
  this->clock_network.start_wifi(ssid, password);

  this->clock_time.begin(ntp_server);

  this->clock_sound.begin(tx, rx);

  this->clock_alarm.begin(this);

  this->clock_display.begin(this, 0x70);
  this->clock_display.register_alarm(&clock_alarm);
  this->clock_display.register_time(&clock_time);

  this->clock_buttons.register_callback(callback);
}

void Clock::tick() {
  clock_time.update();
  clock_alarm.check_alarm(&clock_time);
  clock_display.update_display();
  clock_sound.update_player();
}

int Clock::get_time() {
  return clock_time.get_time_as_integer();
}

int Clock::get_alarm_time() {
  return clock_alarm.get_time_as_integer();
}

void Clock::fire_alarm(ClockAlarm *alarm) {
  Serial.print("Playing sound at volume: "); Serial.println(alarm->get_volume());
  this->clock_sound.volume(alarm->get_volume());
  this->clock_sound.playLargeFolder(alarm->get_folder(), alarm->get_sound());
}

void Clock::kill_alarm() {
  this->clock_sound.stop();
}

void Clock::event_button_pressed(clock_button_t button, bool heldDown) {
  switch (button) {
    case button_next_mode:
      Serial.println("NEXT_MODE");
      event_next_mode(heldDown);
      break;
    case button_next_alarm:
      Serial.println("NEXT ALARM");
      event_set_next_alarm(heldDown);
      break;
    case button_print_debug:
      Serial.println("DEBUG");
      event_debug(heldDown);
      break;
    case button_decrement:
      Serial.println("DEC");
      event_decrement(heldDown);
      break;
    case button_increment:
      Serial.println("INC");
      event_increment(heldDown);
      break;
    case button_next_blink:
      Serial.println("BLINK");
      event_blink(heldDown);
      break;
    case button_play:
      Serial.println("PLAY");
      event_play(heldDown);
      break;
    case button_kill:
      Serial.println("KILL");
      event_kill_alarm(heldDown);
      break;
    default:
      Serial.print("??? Unknown button: "); Serial.println(button);
  }
}

void Clock::event_next_mode(bool heldDown) {
  this->clock_display.next_mode();
}

void Clock::event_debug(bool heldDown) {
  Serial.print("Time: "); Serial.print(this->clock_time.get_hour()); Serial.print(":"); Serial.print(this->clock_time.get_minute()); Serial.print(":"); Serial.println(this->clock_time.get_second());
  Serial.print("Alert: "); Serial.print(this->clock_alarm.get_hour()); Serial.print(":"); Serial.print(this->clock_alarm.get_minute()); Serial.print(":"); Serial.println(this->clock_alarm.get_second());
}

void Clock::event_blink(bool heldDown) {
  this->clock_display.next_blink_rate();
}

void Clock::event_increment(bool heldDown) {
  this->clock_display.increment();
}

void Clock::event_decrement(bool heldDown) {
  this->clock_display.decrement();
}

void Clock::event_play(bool heldDown) {
  this->clock_sound.playLargeFolder(2, 1);
}

void Clock::event_kill_alarm(bool heldDown) {
  this->clock_alarm.kill_alarm();
}

void Clock::event_set_next_alarm(bool heldDown) {
  this->clock_alarm.set_alarm(clock_time.get_hour(), clock_time.get_minute(), clock_time.get_second() + 10);
}
