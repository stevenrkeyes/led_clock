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


// the setup function runs once when you press reset or power the board
void setup() {
  power_led_init(POWER_LED_ENABLE);

  init_brightness_button(INPUT_BUTTON_1);
  init_pattern_button(INPUT_BUTTON_2);

  Serial.begin(9600);

  power_led_heartbeat(POWER_LED_ENABLE);

  delay(2000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  else {
    Serial.println("Found RTC");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  led_array.begin();

  led_array.fill(led_array.Color(0, 0, 0));
  led_array.show();

  run_color_wipe(led_array, led_array.Color(4, 4, 4), 5);

  delay(500);

  led_array.fill(led_array.Color(0, 0, 0));
  led_array.show();

  delay(300);
}

void loop() {
  DateTime now = rtc.now();

  // Check buttons
  int brightness_button_status = get_brightness_button_status();
  int pattern_button_status = get_pattern_button_status();

  // Run Pattern
  if (brightness_button_status) {
    led_array.fill(led_array.Color(3, 3, 3));
    led_array.show();
    delay(200);
  }

  led_array.fill(led_array.Color(0, 0, 0));
  led_array.show();

  delay(10);

}
