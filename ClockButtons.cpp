#include "ClockButtons.hpp"

void ClockButtons::register_callback(KeyCallbackFn callback) {
    IoAbstractionRef pins = ioFrom8754(I2C_ADDRESS_8754, PIN_INTERRUPT);
    switches.initialiseInterrupt(pins, true);
    for (int pin = 0; pin < MAX_KEYS; pin++) {
        switches.addSwitch(pin, callback, 25);
    }
}
