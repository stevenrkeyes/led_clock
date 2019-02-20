/*
  Steven Keyes

  Helper functions for LED patterns
*/

void run_color_wipe(Adafruit_NeoPixel &led_array, uint32_t c, uint8_t wait) {
  for (uint16_t pixel_index=0; pixel_index < led_array.numPixels(); pixel_index++) {
    led_array.setPixelColor(pixel_index, c);
    led_array.show();
    delay(wait);
  }  
}
