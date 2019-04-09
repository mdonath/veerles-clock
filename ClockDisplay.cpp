#include "ClockDisplay.hpp"

#include "Clock.hpp"
#include "ClockAlarm.hpp"
#include "ClockTime.hpp"

#include "ClockUtil.hpp"

void ClockDisplay::begin(Clock* my_clock, uint8_t i2c_address) {
  this->my_clock = my_clock;
  this->matrix = Adafruit_7segment();
  this->matrix.begin(i2c_address);
  this->matrix.setBrightness(this->brightness);
  this->matrix.blinkRate(this->blinkRate);
}

void ClockDisplay::register_alarm(ClockAlarm *alarm) {
  this->alarm = alarm;
}

void ClockDisplay::register_time(ClockTime *clock_time) {
  this->clock_time = clock_time;
}

void ClockDisplay::next_blink_rate() {
  uint8_t blink_rate = ClockUtil::constrain_wrap(this->blinkRate + 1, 0, 3);
  this->set_blink_rate(blink_rate);
}

void ClockDisplay::set_blink_rate(uint8_t blink_rate) {
  this->blinkRate = blink_rate;
  this->matrix.blinkRate(this->blinkRate);
}

void ClockDisplay::increment() {
  switch (this->display_mode) {
    case show_time:
    case show_alarm_countdown:
      break;

    case show_alarm_hour: {
        this->alarm->increment_hour();
        break;
      }
    case show_alarm_minute: {
        this->alarm->increment_minute();
        break;
      }
    case show_volume: {
        this->alarm->increment_volume();
        break;
      }
    case show_brightness: {
        this->increment_brightness();
        break;
      }
  }
}

void ClockDisplay::increment_brightness() {
  this->brightness = ClockUtil::constrain_wrap(this->brightness + 1, 0, 15);
}

void ClockDisplay::decrement_brightness() {
  this->brightness = ClockUtil::constrain_wrap(this->brightness - 1, 0, 15);
}

void ClockDisplay::decrement() {
  switch (this->display_mode) {
    case show_time:
    case show_alarm_countdown:
      break;

    case show_alarm_hour: {
        this->alarm->decrement_hour();
        break;
      }
    case show_alarm_minute: {
        this->alarm->decrement_minute();
        break;
      }
    case show_volume: {
        this->alarm->decrement_volume();
        break;
      }
    case show_brightness: {
        this->decrement_brightness();
        break;
      }
  }
}

void ClockDisplay::next_mode() {
  this->display_mode = static_cast<display_mode_t>((this->display_mode + 1) % number_of_modes);
  previous_value = -1;
}

void ClockDisplay::update_display() {
  switch (this->display_mode) {

    case show_time:
      {
        int counter = this->my_clock->get_time();
        uint8_t sec = this->clock_time->get_second();
        if (sec != previous_value) {
          matrix.writeDigitNum(2, 0x00);
          matrix_draw_counter(counter);
          matrix.drawColon(sec % 2);

          this->set_blink_rate(HT16K33_BLINK_OFF);
          matrix.writeDisplay();
        }
        previous_value = sec;
        break;
      }

    case show_alarm_hour:
    case show_alarm_minute:
      {
        int counter = this->my_clock->get_alarm_time();
        if (counter != previous_value) {
          if (this->display_mode == show_alarm_hour) {
            matrix.writeDigitRaw(2, 0x04);
          } else if (this->display_mode == show_alarm_minute) {
            matrix.writeDigitRaw(2, 0x08);
          }
          matrix_draw_counter(counter);
          this->set_blink_rate(HT16K33_BLINK_2HZ);
          matrix.writeDisplay();
        }
        previous_value = counter;
        break;
      }

    case show_alarm_countdown: {
        uint8_t sec = this->clock_time->get_second();
        if (sec != previous_value) {
          uint8_t mask = sec % 2 == 0 ? 0x04 | 0x08 : 0x02;
          matrix.writeDigitRaw(2, mask);
          int counter = this->clock_time->diff( this->alarm->get_hour(), this->alarm->get_minute(), this->alarm->get_second());
          matrix_draw_counter(counter);
          this->set_blink_rate(HT16K33_BLINK_OFF);
          matrix.writeDisplay();
        }
        previous_value = sec;
        break;
      }

    case show_volume: {
        uint8_t volume = this->alarm->get_volume();
        if (volume != previous_value) {
          matrix.writeDigitRaw(0, 28);
          matrix.writeDigitRaw(1, 0);
          matrix.writeDigitRaw(2, 0);
          matrix.writeDigitNum(3, (volume / 10) % 10);
          matrix.writeDigitNum(4, volume % 10);
          this->set_blink_rate(HT16K33_BLINK_OFF);
          matrix.writeDisplay();
        }
        previous_value = volume;

        break;
      }
    case show_brightness: {
        uint8_t brightness = this->brightness;
        if (brightness != previous_value) {
          matrix.writeDigitRaw(0, 124);
          matrix.writeDigitRaw(1, 0);
          matrix.writeDigitRaw(2, 0);
          matrix.writeDigitNum(3, (brightness / 10) % 10);
          matrix.writeDigitNum(4, brightness % 10);
          matrix.setBrightness(brightness);
          this->set_blink_rate(HT16K33_BLINK_OFF);
          matrix.writeDisplay();
        }
        previous_value = brightness;

        break;
      }
  }
}

void ClockDisplay::matrix_draw_counter(int counter) {
  matrix.writeDigitNum(0, (counter / 1000));
  matrix.writeDigitNum(1, (counter / 100) % 10);
  matrix.writeDigitNum(3, (counter / 10) % 10);
  matrix.writeDigitNum(4, counter % 10);
}
