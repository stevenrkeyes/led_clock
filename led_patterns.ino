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
