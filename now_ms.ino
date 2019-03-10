/*
  Steven Keyes

  Helper function to estimate the current time in ms using the system clock
*/


uint16_t get_now_ms(DateTime now) {
  // Check if the current second has changed to know when to start counting milliseconds
  uint16_t now_sec = now.second();
  static uint16_t prev_sec = now_sec;

  // If this is the first time the function has been called, we'll go ahead and assume we're
  // starting at the first millisecond of the current second, and that the microcontroller clock
  // has just started, so initialize millis_start to 0. This isn't a great assumption, and the
  // result is that the result of this function is not very accurate for the first second.
  static uint16_t millis_start = 0;

  // The number of ms measured by the system clock last second, for correction purposes;
  // Initialize millis_elapsed to 1000, on the assumption that the system clock is perfectly
  // accurate; again, this isn't totally correct, and it means that the result of this function
  // is not very accurate for the first second.
  static uint16_t millis_elapsed = 1000;

  // Check if a new second has begun, to estimate when the millisecond of the current time is 0
  if (prev_sec != now_sec) {
    // Record the number of ms that has elapsed, as measured by the microcontroller clock, since
    // the start of the previous second, for correction.
    millis_elapsed = millis() - millis_start;

    // Reset the point in milliseconds where we are counting from on the microcontroller clock
    millis_start = millis();
  }

  uint16_t now_ms_uncorrected = millis() - millis_start;
  // Scale the time based on the error factor in the previous second
  uint16_t now_ms = (uint16_t)((float) now_ms_uncorrected * 1000 / millis_elapsed);

  // The correction factor could cause the corrected millisecond time to be greater than 1000
  // if the microcontroller clock has changed speed much with respect to the RTC, so clamp the
  // value of now_ms.
  if (now_ms >= 1000) {
    now_ms = 999;
  }

  prev_sec = now_sec;

  return now_ms;
}
