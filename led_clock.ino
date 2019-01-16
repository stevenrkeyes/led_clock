/*
  LED Clock
  
  Steven Keyes

  This is firmware for a LED clock.
*/

#include <Adafruit_NeoPixel.h>
#include "src/SoftPWM/SoftPWM.h"

#define POWER_LED_ENABLE A0
#define MANDALA_DATA A2

Adafruit_NeoPixel led_array = Adafruit_NeoPixel(11*12, MANDALA_DATA, NEO_GRB + NEO_KHZ800);

// the setup function runs once when you press reset or power the board
void setup() {
  // todo: consider turning on POWER_LED_ENABLE before doing anything in order to turn off
  // the annoying power light as soon as possible
  SoftPWMBegin();
  SoftPWMSetFadeTime(POWER_LED_ENABLE, 0, 0);
  SoftPWMSetPolarity(POWER_LED_ENABLE, SOFTPWM_INVERTED);
  SoftPWMSet(POWER_LED_ENABLE, 0);
  //pinMode(POWER_LED_ENABLE, OUTPUT);

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
  //delay(1700);


  led_array.begin();

  for (int i=0; i < led_array.numPixels(); i++) {
    for (int pixel_index=0; pixel_index < led_array.numPixels(); pixel_index++) {
      if (pixel_index <= i){
        led_array.setPixelColor(pixel_index, led_array.Color(4, 4, 4));
      }
      else {
        led_array.setPixelColor(pixel_index, led_array.Color(0, 0, 0));
      }
    }
    led_array.show();
    delay(500);
  }
}

// the loop function runs over and over again forever
void loop() {
}
