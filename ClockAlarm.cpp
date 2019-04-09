#include <Arduino.h>
#include "ClockAlarm.hpp"
#include "Clock.hpp"

#include "ClockUtil.hpp"


void ClockAlarm::begin(Clock *myclock) {
  this->myclock = myclock;
}

int ClockAlarm::get_time_as_integer() {
  return this->tm_hour * 100 + this->tm_min;
}

uint8_t ClockAlarm::get_hour() {
  return this->tm_hour;
}
uint8_t ClockAlarm::get_minute() {
  return this->tm_min;
}
uint8_t ClockAlarm::get_second() {
  return this->tm_sec;
}
int ClockAlarm::get_folder() {
  return this->folder;
}

int ClockAlarm::get_sound() {
  return this->sound;
}

int ClockAlarm::get_volume() {
  return this->volume;
}
void ClockAlarm::check_alarm(ClockTime *clock_time) {
  if (this->armed && !this->running && clock_time->is_equal(this->tm_hour, this->tm_min, this->tm_sec)) {
    this->running = true;
    Serial.println("ALARM!");
    this->myclock->fire_alarm(this);
  }
}

void ClockAlarm::kill_alarm() {
  this->myclock->kill_alarm();
  this->running = false;
  this->armed = false;
  Serial.println("Alarm killed");
}

void ClockAlarm::increment_hour() {
  this->tm_hour = ClockUtil::constrain_wrap(this->tm_hour + 1, 0, 23);
  this->tm_sec = 0;
  this->armed = true;
}

void ClockAlarm::decrement_hour() {
  this->tm_hour = ClockUtil::constrain_wrap(this->tm_hour - 1, 0, 23);
  this->tm_sec = 0;
  this->armed = true;
}

void ClockAlarm::increment_minute() {
  this->tm_min = ClockUtil::constrain_wrap(this->tm_min + 1, 0, 59);
  this->tm_sec = 0;
  this->armed = true;
}

void ClockAlarm::decrement_minute() {
  this->tm_min = ClockUtil::constrain_wrap(this->tm_min - 1, 0, 59);
  this->tm_sec = 0;
  this->armed = true;
}

void ClockAlarm::increment_volume() {
  this->volume = ClockUtil::constrain_wrap(this->volume + 1, 0, 30);
}

void ClockAlarm::decrement_volume() {
  this->volume = ClockUtil::constrain_wrap(this->volume - 1, 0, 30);
}

void ClockAlarm::set_alarm(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec) {
  this->tm_hour = ClockUtil::constrain_wrap(tm_hour, 0, 23);
  this->tm_min = ClockUtil::constrain_wrap(tm_min, 0, 59);
  this->tm_sec = ClockUtil::constrain_wrap(tm_sec, 0, 59);
  this->armed = true;
  this->running = false;
  Serial.print("Alarm set: ");
  Serial.print(tm_hour); Serial.print(":"); Serial.println(tm_min);
}
