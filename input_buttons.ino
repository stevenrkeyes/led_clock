/*
  Steven Keyes

  Helper functions for debouncing and reading the input buttons
*/

Bounce brightness_button = Bounce();
Bounce pattern_button = Bounce();

/*
  Generic and specific functions to initialize the input buttons.
*/
void init_input_button(uint8_t input_button_pin, Bounce &debouncer){
  // Set the internal pullup and associate the pin with the debouncer object
  debouncer.attach(input_button_pin, INPUT_PULLUP);

  // Set the debouncing interval (in ms), determined experimentally
  debouncer.interval(5);
}

void init_brightness_button(uint8_t brightness_button_pin) {
  init_input_button(brightness_button_pin, brightness_button);
}

void init_pattern_button(uint8_t pattern_button_pin) {
  init_input_button(pattern_button_pin, pattern_button);
}

/*
  Generic and specific functions to get the status of an input button; returns 1 if the button
  has been pressed, otherwise 0.
*/
uint8_t get_button_status(Bounce &debouncer) {
  debouncer.update();
  
  return debouncer.fell();
}

uint8_t get_brightness_button_status(){
  return get_button_status(brightness_button);
}

uint8_t get_pattern_button_status(){
  return get_button_status(pattern_button);
}
