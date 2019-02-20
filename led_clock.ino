/*
  LED Clock
  
  Steven Keyes

  This is firmware for a LED clock.
*/

#include <Adafruit_NeoPixel.h>
#include "src/RTClib/RTClib.h"

// Set the debouncing strategy to be "Lock Out" (i.e. register a button press immediately,
// and then wait a cool-down period for subsequent presses), seems good experimentally
#define BOUNCE_LOCK_OUT
// Strangly, this file must be inclueded here even though it is only used in input_buttons.ino;
// a quirk of Arduino
#include "src/Bounce2/src/Bounce2.h"

// Pin Defines
#define PIN_PC0 (14)
#define PIN_PC1 (15)
#define PIN_PC2 (16)
#define PIN_PD5 (11)

// Pin Definitions
#define POWER_LED_ENABLE PIN_PC0
#define MANDALA_DATA     PIN_PC2
#define INPUT_BUTTON_1   PIN_PC1
#define INPUT_BUTTON_2   PIN_PD5

Adafruit_NeoPixel led_array = Adafruit_NeoPixel(11*12, MANDALA_DATA, NEO_GRB + NEO_KHZ800);

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


// the setup function runs once when you press reset or power the board
void setup() {
  power_led_init(POWER_LED_ENABLE);

  power_led_heartbeat(POWER_LED_ENABLE);

  init_brightness_button(INPUT_BUTTON_1);
  init_pattern_button(INPUT_BUTTON_2);

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  else {
    Serial.println("Found RTC");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }


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
    delay(5);
  }
  delay(500);

  for (int pixel_index=0; pixel_index < led_array.numPixels(); pixel_index++) {
    led_array.setPixelColor(pixel_index, led_array.Color(0, 0, 0));
  }
  led_array.show();
  delay(300);
}

void loop() {
  DateTime now = rtc.now();

  // Check buttons
  int brightness_button_status = get_brightness_button_status();
  int pattern_button_status = get_pattern_button_status();

  if (brightness_button_status) {
    for (int pixel_index=0; pixel_index < led_array.numPixels(); pixel_index++) {
      led_array.setPixelColor(pixel_index, led_array.Color(3, 3, 3));
    }
    led_array.show();
    delay(200);
  }

  // Run Pattern

  for (int pixel_index=0; pixel_index < led_array.numPixels(); pixel_index++) {
    led_array.setPixelColor(pixel_index, led_array.Color(0, 0, 0));
  }
  led_array.show();
  delay(10);

}
