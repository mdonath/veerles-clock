#ifndef __CLOCK_BUTTONS_HPP__
#define __CLOCK_BUTTONS_HPP__


// Buttons
#define MAX_KEYS 8
#include <IoAbstraction.h>
#include <IoAbstractionWire.h>


#define PIN_INTERRUPT D7
#define I2C_ADDRESS_8754 0x20

enum clock_button_t {
  button_next_mode,
  button_next_alarm,
  button_print_debug,
  button_decrement,

  button_increment,
  button_next_blink,
  button_kill,
  button_play,
};

class ClockButtons {
  public:

    /**
     * Register the callback function for button presses.
     */
    void register_callback(KeyCallbackFn callback);

  private:

};

#endif
