#ifndef __CLOCK_DISPLAY_HPP__
#define __CLOCK_DISPLAY_HPP__

#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

class Clock;
class ClockAlarm;
class ClockTime;

// Clock Modes
enum display_mode_t {
    show_time,
    show_alarm_hour,
    show_alarm_minute,
    show_alarm_countdown,
    show_volume,
    show_brightness,
    number_of_modes
};

class ClockDisplay {
  public:
    ClockDisplay(){};

    void begin(Clock *my_clock, uint8_t address);
    void register_alarm(ClockAlarm *alarm);
    void register_time(ClockTime *clock_time);

    void increment();
    void decrement();

    void matrix_draw_counter(int counter);
    void update_display();
    void next_mode();
    void next_blink_rate();
    void set_blink_rate(uint8_t blink_rate);

    void increment_brightness();
    void decrement_brightness();

  private:
    display_mode_t display_mode = show_time;

    Clock *my_clock = NULL;
    ClockAlarm *alarm = NULL;
    ClockTime *clock_time = NULL;

    uint8_t brightness = 0;
    uint8_t blinkRate = 0;

    int previous_value = 0;

    Adafruit_7segment matrix;
};

#endif
