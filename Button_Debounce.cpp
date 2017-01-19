#include "Button_Debounce.h"

BasicDebounce::BasicDebounce(const uint8_t pin_number,
			     const unsigned int delay_ms,
			     const uint8_t  true_on,
			     const SetUpPinCommand setUpPinCommand):_true_on(true_on) {
    (*setUpPinCommand)(pin_number);
    _bouncer.attach(pin_number);
    _bouncer.interval(delay_ms);
}

void BasicDebounce::update() {
    _bouncer.update();

    if ( _bouncer.rose() ) {
	if ( _true_on ) {
	    if (_button_pressed_command) {
		(*_button_pressed_command)(this);
	    }
	} else {
	    if (_button_released_command) {
		(*_button_released_command)(this);
	    }
	}
	_entered_state_time = millis();
    }

    if ( _bouncer.fell() ) {
	if ( _true_on ) {
	    if (_button_released_command) {
		(*_button_released_command)(this);
	    }
	} else {
	    if (_button_pressed_command) {
		(*_button_pressed_command)(this);
	    }
	}
	_entered_state_time = millis();
    }
}

bool BasicDebounce::set_pressed_command(Command command) {
    bool existed = _button_pressed_command;
    _button_pressed_command = command;
    return existed;
}

bool BasicDebounce::set_released_command(Command command) {
    bool existed = _button_released_command;
    _button_released_command = command;
    return existed;
}

bool BasicDebounce::set_button_pressed_callback(Command command) {
    return this->set_pressed_command(command);
}

bool BasicDebounce::set_button_released_callback(Command command) {
    return this->set_released_command(command);
}
