#ifndef BUTTON_DEBOUNCE_H
#define BUTTON_DEBOUNCE_H
#include "Arduino.h"


class BasicDebounce {
    //If std function takes up too much resources, can switch to function pointers.
    //Assumes a button is low when it is pressed/acitivated/true.
    // Considering pressed to be "true"
public:
    using Command = void (*)(BasicDebounce*);
    BasicDebounce(const uint8_t pin_number,
		  const unsigned int delay_ms,
		  const uint8_t true_on = LOW);
    void update();

    // For both of these, return if we had some value set for these prior.
    // To get the time the button has been in said state for, one can just use
    // query, 
    bool set_pressed_command(Command command);
    bool set_released_command(Command command);

    //True if the debounced reading is considered to be true.
    // While the commands implicitly give you this info, and are happen onstate edges
    // it should be valid to call this during a command.
    bool query() {
	return _has_true;
    }

    // How long the button has been in it's current state for.
    // Decided to make these into two separate functions than overloading query
    long time_in_current_state() {
        return millis() - _last_change_time;
    }

    // How long we have been in our current state
    /*
     *  IMPORTANT NOTE: When a command is called, this tells you how long
     *  the button was in the state it is currently leaving. For example,
     *  if a button is released, and the released command is run, calling
     *  this function from the released command will give you how long the button
     *  was pressed. This lets you perform an action on release/press if the button
     *  was pressed/released for N seconds.  While a bit misleading, technically
     *  the command is run while the state is changing, and this is a lot more useful
     *  than having this function always return 0 when called from a command.
     *
     */
    unsigned long time_in_state() {
	return millis() - _entered_state_time;
    }

    // Depreciated, going with shorter, more sensible names, but otherwise same as
    // the earlier setting functions.
    bool set_button_pressed_callback(Command command);
    bool set_button_released_callback(Command command);
    // End depreciated


private:
    // This tells you when we entered the current state at
    unsigned long _entered_state_time = 0;
    // The last time the button reading changed, raw
    unsigned long _last_change_time = 0;
    // What int reading counts as true
    const uint8_t  _true_on;
    // A debounced state of if the button is currently reading true
    bool _has_true = false;
    // A raw, bouncy state of if the button is readly reading true
    bool _current_state = false;
    // Pin number of the button
    const uint8_t _pin_number;
    // How long a button must stay in a position to be seen as true
    const unsigned int _delay_ms;
    // The two commands to run when a button is pressed or released
    Command  _button_pressed_command = 0;
    Command _button_released_command = 0;

};

#endif
