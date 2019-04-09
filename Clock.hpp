#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include "ClockAlarm.hpp"
#include "ClockButtons.hpp"
#include "ClockDisplay.hpp"
#include "ClockNetwork.hpp"
#include "ClockSound.hpp"
#include "ClockTime.hpp"

class Clock {
  public:
    void begin(int tx, int rx, KeyCallbackFn callback, const char *ssid, const char *password, const char *ntp_server);

    void tick();

    void event_button_pressed(clock_button_t pin, bool heldDown);

    int get_time();
    int get_alarm_time();

    void fire_alarm(ClockAlarm *alarm);
    void kill_alarm();

  private:
    void event_next_mode(bool heldDown);
    void event_increment(bool heldDown);
    void event_decrement(bool heldDown);
    void event_kill_alarm(bool heldDown);
    void event_play(bool heldDown);
    void event_blink(bool heldDown);
    void event_set_next_alarm(bool heldDown);
    void event_debug(bool heldDown);

    ClockTime clock_time;
    ClockSound clock_sound;
    ClockButtons clock_buttons;
    ClockDisplay clock_display;
    ClockAlarm clock_alarm;
    ClockNetwork clock_network;
};

#endif
