#ifndef BUTTON_DEBOUNCE_H
#define BUTTON_DEBOUNCE_H
#include "Arduino.h"
#include <Bounce2.h>


class BasicDebounce {

public:
    using Command = void (*)(BasicDebounce*);
    using SetUpPinCommand = void (*)(int);

private:
    static void InitPinToPullUp(int pin) {
        // Setup the button
        pinMode( pin,INPUT_PULLUP);
    }
public:
    BasicDebounce(const uint8_t pin_number,
		  const unsigned int delay_ms,
		  const uint8_t true_on = LOW,
                  const SetUpPinCommand setUpPinCommand = InitPinToPullUp);


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
	return _bouncer.read() == _true_on;
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
    // What int reading counts as true
    const uint8_t  _true_on;

    Bounce _bouncer;
    Bounce* _bouncer2;
    Command  _button_pressed_command = 0;
    Command _button_released_command = 0;

};

#endif
