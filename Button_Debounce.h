#ifndef BUTTON_DEBOUNCE_H
#define BUTTON_DEBOUNCE_H
#include "Arduino.h"

//License : GPLV3

class BasicDebounce {
    //If std function takes up too much resources, can switch to function pointers.
    //Assumes a button is low when it is pressed/acitivated/true.
    // Considering pressed to be "true"
public:
    BasicDebounce(const uint8_t pin_number, const unsigned int delay_ms, const uint8_t true_on = LOW);
    void update();
    // For both of these, return if we had some value set for these prior.
    bool set_button_pressed_callback(void (*callback)());
    // Todo, add a second one of these with a long parameter for how long the
    // button was held down for.
    bool set_button_released_callback(void (*callback)());

    //True if the debounced reading is considered to be true.
    // TODO return how long the reading has been true for.
    // Which will then be implicitly converted into a bool if that's what is desired.
    bool query() {
	return _has_true;
    }

private:

    unsigned long _last_change_time = 0;  // the last time the trigger was released
    const uint8_t  _true_on;
    bool _has_true = false;
    bool _last_state_debounce = false;
    const uint8_t _pin_number;
    const unsigned int _delay_ms;
    void  (*_button_pressed_callback)() = 0;
    void (*_button_released_callback)() = 0;

};

#endif
