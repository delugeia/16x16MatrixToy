#pragma once
#include "../global.hpp"
#include "Precision.hpp"

void DrawMarqueeComparison() {
  FastLED.clear(false);

  const float widthWithGap = 6.0f;
  static float scroll = 0.0f;
  scroll += 0.03f;

  if (scroll > widthWithGap) {
    scroll -= widthWithGap;
  }

  for (float index = scroll; index < NUM_LEDS / 2 - 1; index += widthWithGap) {
    DrawPixels(index, 3, CRGB::Green);
    DrawPixels(NUM_LEDS - 1 - (int)index, 3, CRGB::Red);
  }
}
