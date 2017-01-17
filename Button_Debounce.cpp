#include "Button_Debounce.h"

BasicDebounce::BasicDebounce(const uint8_t pin_number,
			     const unsigned int delay_ms,
			     const uint8_t  true_on):_pin_number(pin_number),_delay_ms(delay_ms),_true_on(true_on) {
}

void BasicDebounce::update() {
  int val = digitalRead(_pin_number);
  bool reading = (val == _true_on);

  if (reading != _last_state_debounce) {
    // reset the debouncing timer
    _last_change_time = millis();
  }

  if ((millis() - _last_change_time) > _delay_ms) {

    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

       if ( reading && !_has_true) {
	   //Button is depressed
	   if ( _button_pressed_callback ) {
	       (*_button_pressed_callback)();
	   }
        _has_true = true;
       } else if (!reading) {
          _has_true = false;
	  if ( _button_released_callback ) {
	      (*_button_released_callback)();
	  }
       }
  }
  _last_state_debounce = reading;
}

bool BasicDebounce::set_button_pressed_callback(void (*callback)()) {
    bool existed = _button_pressed_callback;
    _button_pressed_callback = callback;
    return existed;
}

bool BasicDebounce::set_button_released_callback(void (*callback)()) {
    bool existed = _button_released_callback;
    _button_released_callback = callback;
    return existed;
}
