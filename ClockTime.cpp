#include "ClockTime.hpp"


void ClockTime::begin(const char* ntp_server) {
  configTime(0, 0, ntp_server);
  setenv("TZ", "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
  this->update();
}

uint8_t ClockTime::get_second() {
  return this->timeinfo.tm_sec;
}

uint8_t ClockTime::get_minute() {
  return this->timeinfo.tm_min;
}

uint8_t ClockTime::get_hour() {
  return this->timeinfo.tm_hour;
}
int ClockTime::diff(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec) {
  int hourDiff = tm_hour - this->timeinfo.tm_hour;
  int minDiff = tm_min - this->timeinfo.tm_min;
  int secDiff = tm_sec - this->timeinfo.tm_sec;
  if (secDiff < 0) {
    minDiff--;
    secDiff += 60;
  }
  if (secDiff > 59) {
    minDiff++;
    secDiff -= 60;
  }
  if (minDiff < 0) {
    hourDiff--;
    minDiff += 60;
  }
  if (minDiff > 59) {
      hourDiff++;
      minDiff -= 60;
  }
  if (hourDiff < 0) {
    hourDiff += 24;
  }
  if (hourDiff == 0) {
    return minDiff * 100 + secDiff;
  }
  return hourDiff * 100 + minDiff;
}

bool ClockTime::is_equal(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec) {
  return this->timeinfo.tm_hour == tm_hour
         && this->timeinfo.tm_min == tm_min
         && this->timeinfo.tm_sec == tm_sec;
}

int ClockTime::get_time_as_integer() {
  return this->timeinfo.tm_hour * 100  + this->timeinfo.tm_min;
}

void ClockTime::update() {
  time_t rawtime = time(nullptr);
  localtime_r(&rawtime, &timeinfo);
}
