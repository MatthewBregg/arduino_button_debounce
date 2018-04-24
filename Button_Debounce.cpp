#include "Button_Debounce.h"

BasicDebounce::BasicDebounce(const uint8_t pin_number,
			     const byte delay_ms,
			     const uint8_t  true_on,
			     const SetUpPinCommand setUpPinCommand):_true_on(true_on),_delay_ms(delay_ms) {
    (*setUpPinCommand)(pin_number);
    _bouncer.attach(pin_number);
    _bouncer.interval(delay_ms);
}

void BasicDebounce::AddSecondaryPin(const int8_t pin_number, const SetUpPinCommand setUpPinCommand) {
    (*setUpPinCommand)(pin_number);
    _bouncer2 = new Bounce();
    _bouncer2->attach(pin_number);
    _bouncer2->interval(_delay_ms);
}

void BasicDebounce::handle_rose_command() {
	if ( _true_on == HIGH ) {
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

void BasicDebounce::handle_fell_command() {

    if ( _true_on == HIGH ) {
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

void BasicDebounce::update() {
<<<<<<< HEAD
    _bouncer.update();

    if ( _bouncer2 ) {

	if ( _bouncer.rose() && _bouncer2->read() == LOW ) {
	    handle_rose_command();
	    return;
	}

	if ( _bouncer.read() == HIGH && _bouncer2->fell()) {
	    handle_rose_command();
	    return;
	}

	if ( _bouncer.fell() && _bouncer2->read() == HIGH) {
	    handle_fell_command();
	    return;
	}

	if ( _bouncer.read() == LOW && _bouncer2->rose()) {
	    handle_fell_command();
	    return;
	}
    } else {
	if ( _bouncer.rose() ) {
	    handle_rose_command();
	}
	if ( _bouncer.fell() ) {
	    handle_fell_command();
	}
    }

=======
  int val = digitalRead(_pin_number);
  bool reading = (val == _true_on);

  if (reading != _current_state) {
    // reset the debouncing timer
    _last_change_time = millis();
  }

  if ((millis() - _last_change_time) > _delay_ms) {

    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

       if ( reading && !_has_true) {
	   //Button is depressed
	   _has_true = true;
	   if ( _button_pressed_command ) {
	       (*_button_pressed_command)(this);
	   }
	   _entered_state_time = millis();
       } else if (!reading && _has_true) {
          _has_true = false;
	  if ( _button_released_command ) {
	      (*_button_released_command)(this);
	  }
	   _entered_state_time = millis();
       }
  }
  _current_state = reading;
>>>>>>> cf5b48b11b7ed06f2767e3f6bd3d20135429ef0c
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
