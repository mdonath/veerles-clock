#ifndef __CLOCK_UTIL_HPP__
#define __CLOCK_UTIL_HPP__

#include <Arduino.h>

class ClockUtil {
  public:
    static uint8_t constrain_wrap(int8_t value, uint8_t minimum, uint8_t maximum) {
      if (value > maximum) {
        return minimum;
      }
      if (value < 0) {
        return maximum;
      }
      return value;
    }
};

#endif
