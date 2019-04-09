#ifndef __CLOCK_TIME_HPP__
#define __CLOCK_TIME_HPP__

#include <Arduino.h>

class ClockTime {
  public:
    void begin(const char* ntp_server);
    void update();
    int get_time_as_integer();

    uint8_t get_second();
    uint8_t get_minute();
    uint8_t get_hour();
    
    bool is_equal(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec);
    int diff(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec);

  private:
    struct tm timeinfo;
};

#endif
