/*
  Steven Keyes

  Helper functions for running and animating the power LED
*/

#include "src/SoftPWM/SoftPWM.h"

void power_led_init(uint8_t power_led_pin) {
  // Turn on POWER_LED_ENABLE (an active low signal) before doing anything in order to turn off
  // the annoying power LED as soon as possible
  digitalWrite(power_led_pin, HIGH);
  pinMode(power_led_pin, OUTPUT);

  // This pin is not connected to a PWM peripheral and needs to be modulated in software
  SoftPWMBegin();
  SoftPWMSetFadeTime(power_led_pin, 0, 0);
  // The signal is actually a "disable" signal (the LED turns off when the pin is high), so invert
  // the signal to be an "enable" signal in all subsequent calls
  SoftPWMSetPolarity(power_led_pin, SOFTPWM_INVERTED);

  // Start with the LED off
  SoftPWMSet(power_led_pin, 0);
}

void power_led_heartbeat(uint8_t power_led_pin) {
  for (int fadeValue = 0 ; fadeValue <= 130; fadeValue += 10) {
    SoftPWMSet(power_led_pin, fadeValue);
    delay(15);
  }
  for (int fadeValue = 130 ; fadeValue >= 0; fadeValue -= 10) {
    SoftPWMSet(power_led_pin, fadeValue);
    delay(15);
  }
  delay(50);
  for (int fadeValue = 0 ; fadeValue <= 40; fadeValue += 5) {
    SoftPWMSet(power_led_pin, fadeValue);
    delay(15);
  }
  for (int fadeValue = 40 ; fadeValue >= 0; fadeValue -= 5) {
    SoftPWMSet(power_led_pin, fadeValue);
    delay(15);
  }  
}
