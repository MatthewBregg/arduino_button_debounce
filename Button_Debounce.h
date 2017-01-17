#ifndef BUTTON_DEBOUNCE_H
#define BUTTON_DEBOUNCE_H
#include "Arduino.h"

//License : GPLV3

class BasicDebounce {
    //If std function takes up too much resources, can switch to function pointers.
    //Assumes a button is low when it is pressed/acitivated/true.
    // Considering pressed to be "true"
public:
    using Command = void (*)(BasicDebounce*);
    BasicDebounce(const uint8_t pin_number, const unsigned int delay_ms, const uint8_t true_on = LOW);
    void update();

    // For both of these, return if we had some value set for these prior.
    // To get the time the button has been in said state for, one can just use
    // query, 
    bool set_pressed_command(Command command);
    bool set_released_command(Command command);

    //True if the debounced reading is considered to be true.
    bool query() {
	return _has_true;
    }

    // How long the button has been in it's current state for.
    // Decided to make these into two seprate funtions than overloading query
    long time_in_current_state() {
        return millis() - _last_change_time;
    }



    // Depreciated, going with shorter, more sensible names, but otherwise same as
    // the earlier setting functions.
    bool set_button_pressed_callback(Command command);
    bool set_button_released_callback(Command command);
    // End depreciated


private:

    unsigned long _last_change_time = 0;  // the last time the trigger was released
    const uint8_t  _true_on;
    bool _has_true = false;
    bool _current_state = false;
    const uint8_t _pin_number;
    const unsigned int _delay_ms;
    Command  _button_pressed_command = 0;
    Command _button_released_command = 0;

};

#endif
