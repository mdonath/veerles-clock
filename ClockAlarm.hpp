#ifndef __CLOCK_ALARM_HPP__
#define __CLOCK_ALARM_HPP__

#include <Arduino.h>

class Clock;
class ClockTime;

class ClockAlarm {
  public:
    ClockAlarm():
      armed(false),
      running(false),
      folder(2),
      sound(2),
      volume(10)
    {};

    void begin(Clock *myclock);
    void set_alarm(uint8_t tm_hour, uint8_t tm_min, uint8_t tm_sec);
    void check_alarm(ClockTime *clock_time);

    void fire_alarm();
    void kill_alarm();

    void increment_hour();
    void decrement_hour();
    void increment_minute();
    void decrement_minute();
    void increment_volume();
    void decrement_volume();

    int get_time_as_integer();
    uint8_t get_hour();
    uint8_t get_minute();
    uint8_t get_second();
    int get_folder();
    int get_sound();
    int get_volume();

  private:
    Clock *myclock;

    uint8_t tm_hour;
    uint8_t tm_min;
    uint8_t tm_sec;

    bool armed;
    bool running;

    int folder;
    int sound;
    int volume;

    uint8_t constrain_wrap(int8_t value, uint8_t minimum, uint8_t maximum);
};

#endif
