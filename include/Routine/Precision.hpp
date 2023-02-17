#pragma once
#include "../global.hpp"

CRGB ColorFraction(CRGB colorIn, float fraction) {
  fraction = min(1.0f, fraction);
  return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void DrawPixels(float fPos, float count, CRGB color) {
  float availFirstPixel = 1.0f - (fPos - (long)(fPos));
  float amtFirstPixel = min(availFirstPixel, count);  // edge case where sub-pixal total distance
  float remaining = min(count, FastLED.size() - fPos);
  int iPos = fPos;

  if (remaining > 0.0f) {
    FastLED.leds()[iPos++] += ColorFraction(color, amtFirstPixel);
    remaining -= amtFirstPixel;
  }

  while (remaining > 1.0f) {
    FastLED.leds()[iPos++] += color;
    remaining--;
  }

  if (remaining > 0.0f) {
    FastLED.leds()[iPos] += ColorFraction(color, remaining);
  }
}
