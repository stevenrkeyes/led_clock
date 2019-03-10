/*
  Steven Keyes

  Helper functions for LED patterns
*/

const uint8_t big_tip_dots[] = {10, 32, 54, 76, 98, 120};

const uint8_t little_tip_dots[] = {15, 37, 59, 81, 103, 125};

const uint8_t tip_dots[] = {10, 15, 32, 37, 54, 59, 76, 81, 98, 103, 120, 125};

const uint8_t left_pointing_edges[] = {10, 11, 12, 13, 16, 18, 19, 20, 21, 32, 33, 34, 35, 38, 40, 41, 42, 43, 54, 55, 56, 57, 60, 62, 63, 64, 65, 76, 77, 78, 79, 82, 84, 85, 86, 87, 98, 99, 100, 101, 104, 106, 107, 108, 109, 120, 121, 122, 123, 126, 128, 129, 130, 131};

const uint8_t right_pointing_edges[] = {0, 1, 2, 3, 5, 7, 8, 9, 10, 22, 23, 24, 25, 27, 29, 30, 31, 32, 44, 45, 46, 47, 49, 51, 52, 53, 54, 66, 67, 68, 69, 71, 73, 74, 75, 76, 88, 89, 90, 91, 93, 95, 96, 97, 98, 110, 111, 112, 113, 115, 117, 118, 119, 120};

const uint8_t outside_edge[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125};

const uint8_t middle_circle[] = {3, 4, 17, 18, 25, 26, 39, 40, 47, 48, 61, 62, 69, 70, 83, 84, 91, 92, 105, 106, 113, 114, 127, 128};

const uint8_t big_leaves[] = {0, 1, 2, 3, 5, 7, 8, 9, 10, 11, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 25, 27, 29, 30, 31, 32, 33, 34, 35, 38, 40, 41, 42, 43, 44, 45, 46, 47, 49, 51, 52, 53, 54, 55, 56, 57, 60, 62, 63, 64, 65, 66, 67, 68, 69, 71, 73, 74, 75, 76, 77, 78, 79, 82, 84, 85, 86, 87, 88, 89, 90, 91, 93, 95, 96, 97, 98, 99, 100, 101, 104, 106, 107, 108, 109, 110, 111, 112, 113, 115, 117, 118, 119, 120, 121, 122, 123, 126, 128, 129, 130, 131};

const uint8_t little_leaves[] = {6, 14, 15, 28, 36, 37, 50, 58, 59, 72, 80, 81, 94, 102, 103, 116, 124, 125};

const uint8_t inner_circle[] = {0, 21, 22, 43, 44, 65, 66, 87, 88, 109, 110, 131};

void run_color_wipe(Adafruit_NeoPixel &led_array, uint32_t c, uint8_t wait) {
  for (uint16_t pixel_index = 0; pixel_index < led_array.numPixels(); pixel_index++) {
    led_array.setPixelColor(pixel_index, c);
    led_array.show();
    delay(wait);
  }
}

void run_solid(Adafruit_NeoPixel &led_array, const uint8_t *pixel_subset, uint8_t pixel_subset_len, uint32_t c) {
  led_array.fill(led_array.Color(0, 0, 0));
  for (uint8_t i = 0; i < pixel_subset_len; i++) {
    uint8_t pixel_index = pixel_subset[i];
    led_array.setPixelColor(pixel_index, c);
  }
  led_array.show();
}

void run_pattern(Adafruit_NeoPixel &led_array) {
  run_solid(led_array, big_tip_dots, sizeof(big_tip_dots), led_array.Color(4, 4, 4));
}

void show_basic_clock_frame(Adafruit_NeoPixel &led_array, uint8_t brightness_level, DateTime now)
{
  uint16_t unnormalized_brightness_val = brightness_level * MAX_BRIGHTNESS;
  uint8_t brightness_val = unnormalized_brightness_val / MAX_BRIGHTNESS_LEVEL;

  led_array.fill(led_array.Color(0, 0, 0));

  // Show the hour on the little circle
  uint8_t hour_pixel_index = (now.hour() % 12) * sizeof(inner_circle) / 12;
  hour_pixel_index = sizeof(inner_circle) - 1 - hour_pixel_index;
  hour_pixel_index = (hour_pixel_index + sizeof(inner_circle) + 1) % sizeof(inner_circle);
  led_array.setPixelColor(inner_circle[hour_pixel_index], led_array.Color(brightness_val, brightness_val, brightness_val));

  // Show the minute on the middle circle
  uint8_t minute_pixel_index = now.minute() * sizeof(middle_circle) / 60;
  minute_pixel_index = sizeof(middle_circle) - 1 - minute_pixel_index;
  minute_pixel_index = (minute_pixel_index + sizeof(middle_circle) + 2) % sizeof(middle_circle);
  led_array.setPixelColor(middle_circle[minute_pixel_index], led_array.Color(brightness_val, brightness_val, brightness_val));

  // Show the second on the outline
  uint8_t second_pixel_index = now.second() * sizeof(outside_edge) / 60;
  second_pixel_index = sizeof(outside_edge) - 1 - second_pixel_index;
  second_pixel_index = (second_pixel_index + sizeof(outside_edge) + 5) % sizeof(outside_edge);
  led_array.setPixelColor(outside_edge[second_pixel_index], led_array.Color(brightness_val, brightness_val, brightness_val));

  led_array.show();
}

#define DECREMENT_AMOUNT (1)

void show_sparkle_frame(Adafruit_NeoPixel &led_array, uint8_t brightness_level, DateTime now)
{
  // Every time a frame of this pattern occurs, each LED has a low probability of illuminating

  for (uint8_t pixel_index = 0; pixel_index < led_array.numPixels(); pixel_index++) {
    uint32_t current_color = led_array.getPixelColor(pixel_index);
    if (random(200) > 197) {
      led_array.setPixelColor(pixel_index, led_array.Color(brightness_level, brightness_level, brightness_level));
    }
    else {
      uint8_t r = (uint8_t)(current_color >> 16);
      uint8_t g = (uint8_t)(current_color >> 8);
      uint8_t b = (uint8_t) current_color;
      if (r > DECREMENT_AMOUNT) {
        r -= DECREMENT_AMOUNT;
      }
      else {
        r = 0;
      }
      if (g > DECREMENT_AMOUNT) {
        g -= DECREMENT_AMOUNT;
      }
      else {
        g = 0;
      }
      if (b > DECREMENT_AMOUNT) {
        b -= DECREMENT_AMOUNT;
      }
      else {
        b = 0;
      }
      led_array.setPixelColor(pixel_index, led_array.Color(r, g, b));

    }
  }
  led_array.show();
}

// Input a value 0 to 3 * brightness_val to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(Adafruit_NeoPixel &led_array, uint16_t wheel_pos, uint8_t brightness_val) {
  uint8_t r, g, b;
  wheel_pos = 3 * brightness_val - wheel_pos;
  if (wheel_pos < brightness_val) {
    r = brightness_val - wheel_pos;
    g = 0;
    b = wheel_pos;
    return led_array.Color(r, g, b);
  }
  if (wheel_pos < 2 * brightness_val) {
    wheel_pos -= brightness_val;
    r = 0;
    g = wheel_pos;
    b = brightness_val - wheel_pos;
    return led_array.Color(r, g, b);
  }
  wheel_pos -= 2 * brightness_val;
  r = wheel_pos;
  g = brightness_val - wheel_pos;
  b = 0;
  return led_array.Color(r, g, b);
}

uint8_t get_heartbeat_value(DateTime now, uint16_t now_ms, uint8_t brightness_val, uint16_t period_sec) {
  float total_time_ms = now.second() * 1000 + now_ms;
  float elapsed_time_ms = fmod(total_time_ms, period_sec * 1000);

  float heartbeat_val_float = 0;

  if (elapsed_time_ms < 250) {
    heartbeat_val_float = brightness_val * (elapsed_time_ms / 250);
  }
  else if (elapsed_time_ms < 500) {
    heartbeat_val_float = brightness_val * (1 - ((elapsed_time_ms - 250) / 250));
  }
  else if (elapsed_time_ms < 550) {
    heartbeat_val_float = 0;
  }
  else if (elapsed_time_ms < 750) {
    heartbeat_val_float = 0.8 * brightness_val * ((elapsed_time_ms - 550) / 200);
  }
  else if (elapsed_time_ms < 950) {
    heartbeat_val_float = 0.8 * brightness_val * (1 - ((elapsed_time_ms - 750) / 200));
  }
  else {
    heartbeat_val_float = 0;
  }

  return (uint8_t) heartbeat_val_float;
}

void show_slow_rainbow_frame(Adafruit_NeoPixel &led_array, uint8_t brightness_level, DateTime now, uint16_t now_ms)
{
  // Fades through a rainbow over the course of a day

  uint16_t unnormalized_brightness_val = brightness_level * MAX_BRIGHTNESS;
  uint8_t brightness_val = unnormalized_brightness_val / MAX_BRIGHTNESS_LEVEL;

  led_array.fill(led_array.Color(0, 0, 0));

  // Convert the time of day to a number from 0 to 255
  uint16_t now_minutes = now.hour() * 60 + now.minute();
  uint16_t max_wheel = brightness_val * 3;
  uint32_t now_minutes_normalized = now_minutes * max_wheel / (24 * 60);

  uint32_t current_color = wheel(led_array, (uint16_t) now_minutes_normalized, brightness_val);

  uint8_t r = (uint8_t)(current_color >> 16);
  uint8_t g = (uint8_t)(current_color >> 8);
  uint8_t b = (uint8_t) current_color;

  uint8_t heartbeat_brightness = brightness_val * 0.7;
  uint8_t heartbeat_val = get_heartbeat_value(now, now_ms, heartbeat_brightness, 3);
  r = max(r, heartbeat_val);
  g = max(g, heartbeat_val);
  b = max(b, heartbeat_val);

  uint32_t current_color_with_heartbeat = led_array.Color(r, g, b);

  for (uint8_t pixel_index = 0; pixel_index < led_array.numPixels(); pixel_index++) {
    led_array.setPixelColor(pixel_index, current_color);
  }
  for (uint8_t i = 0; i < sizeof(middle_circle); i++) {
    uint8_t pixel_index = middle_circle[i];
    led_array.setPixelColor(pixel_index, current_color_with_heartbeat);
  }
  led_array.show();
}

#define CYCLE_TIME_MS (10000)

void show_rainbow_cycle_frame(Adafruit_NeoPixel &led_array, uint8_t brightness_level, DateTime now, uint16_t now_ms)
{
  // Applies a rainbow cycle that wraps around the led array

  uint16_t unnormalized_brightness_val = brightness_level * MAX_BRIGHTNESS;
  uint8_t brightness_val = unnormalized_brightness_val / MAX_BRIGHTNESS_LEVEL;

  led_array.fill(led_array.Color(0, 0, 0));

  // The RTC doesn't have ms precision, but I want this pattern to move faster than once a second,
  // so use the microcontroller clock (imprecise for long term timing)
  uint32_t elapsed_time_ms = (now_ms + 1000 * now.second()) % CYCLE_TIME_MS;
  float fraction_complete = ((float)elapsed_time_ms / CYCLE_TIME_MS);
  float max_wheel = brightness_val * 3;
  float base_wheel_position = max_wheel * fraction_complete;

  for (int pixel_index = 0; pixel_index < led_array.numPixels(); pixel_index++) {
    float pixel_wheel_position_unbounded = (pixel_index * max_wheel / led_array.numPixels()) + base_wheel_position;
    uint16_t pixel_wheel_position = fmod(pixel_wheel_position_unbounded, max_wheel);
    uint32_t color = wheel(led_array, pixel_wheel_position, brightness_val);
    led_array.setPixelColor(pixel_index, color);
  }

  for (uint8_t i = 0; i < sizeof(big_leaves); i++) {
    uint8_t pixel_index = big_leaves[i];
    uint32_t current_color = led_array.getPixelColor(pixel_index);

    uint8_t r = (uint8_t)(current_color >> 16);
    uint8_t g = (uint8_t)(current_color >> 8);
    uint8_t b = (uint8_t) current_color;

    // Todo: clean up this black magic one-liner
    uint8_t pulse_brightness = brightness_val * 0.9 * abs(2.0 * (fmod((float)i + 2 * sizeof(big_leaves) * (1 - fraction_complete), sizeof(big_leaves)) / sizeof(big_leaves)) - 1.0);
    r = max(r, pulse_brightness);
    g = max(g, pulse_brightness);
    b = max(b, pulse_brightness);
    uint32_t current_color_with_pulse = led_array.Color(r, g, b);

    led_array.setPixelColor(pixel_index, current_color_with_pulse);
  }

  led_array.show();
}

uint8_t triangle(uint8_t phase) {
  phase = phase % 255;
  if (phase < 128)
  {
    return phase;
  }
  else
  {
    return 255 - phase;
  }
}

void show_red_pulse_clock_frame(Adafruit_NeoPixel &led_array, uint8_t brightness_level, DateTime now, uint16_t now_ms)
{
  // Displays a mostly red background with dark pulses and yellow pulses moving around

  double total_time_ms = (now.minute() * 60 + now.second()) * 1000 + now_ms;

  uint16_t unnormalized_brightness_val = brightness_level * MAX_BRIGHTNESS;
  uint8_t brightness_val = unnormalized_brightness_val / MAX_BRIGHTNESS_LEVEL;

  led_array.fill(led_array.Color(0, 0, 0));

  for (int pixel_index = 0; pixel_index < led_array.numPixels(); pixel_index++) {
    uint8_t r = brightness_val * (1.0 / 255) * (120 + 0.5 * (triangle(0.04 * total_time_ms + 20 * pixel_index)));
    uint8_t g = brightness_val * (0.7 / 255) * (triangle(0.08 * total_time_ms + 20 * pixel_index + 127));
    uint8_t b = brightness_val * (0.5 / 255) * (triangle(0.08 * total_time_ms + 20 * pixel_index + 127));
    led_array.setPixelColor(pixel_index, led_array.Color(r, g, b));
  }

  led_array.show();
}
