/*
  LED Clock
  
  Steven Keyes

  This is firmware for a LED clock.
*/

#include "src/SoftPWM/SoftPWM.h"

#define POWER_LED_ENABLE A0

// the setup function runs once when you press reset or power the board
void setup() {
  SoftPWMBegin();
  SoftPWMSetFadeTime(POWER_LED_ENABLE, 0, 0);
  SoftPWMSetPolarity(POWER_LED_ENABLE, SOFTPWM_INVERTED);
  SoftPWMSet(POWER_LED_ENABLE, 0);
  //pinMode(POWER_LED_ENABLE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int fadeValue = 0 ; fadeValue <= 130; fadeValue += 10) {
    SoftPWMSet(POWER_LED_ENABLE, fadeValue);
    delay(15);
  }
  for (int fadeValue = 130 ; fadeValue >= 0; fadeValue -= 10) {
    SoftPWMSet(POWER_LED_ENABLE, fadeValue);
    delay(15);
  }
  delay(50);
  for (int fadeValue = 0 ; fadeValue <= 40; fadeValue += 5) {
    SoftPWMSet(POWER_LED_ENABLE, fadeValue);
    delay(15);
  }
  for (int fadeValue = 40 ; fadeValue >= 0; fadeValue -= 5) {
    SoftPWMSet(POWER_LED_ENABLE, fadeValue);
    delay(15);
  }  
  delay(1700);
}
