#pragma once
#include "../global.hpp"

namespace R_Twinkle {

uint8_t buttonPresses = 1;

uint8_t fadeAmt = 0;
uint8_t fadeSteps = 2;
uint8_t fadeIncrement = 32;

#define NUM_COLORS 5
static const CRGB TwinkleColors[NUM_COLORS] = {CRGB::Red, CRGB::Blue, CRGB::Purple, CRGB::Green, CRGB::Orange};

void Draw(bool buttonB) {
  if (buttonB) {
    buttonPresses = ++buttonPresses %= fadeSteps + 1;
    fadeAmt = buttonPresses * fadeIncrement;
  }

  fadeToBlackBy(g_LEDs, NUM_LEDS, fadeAmt);
  g_LEDs[random(NUM_LEDS)] = TwinkleColors[random(NUM_COLORS)];
}

}  // namespace Twinkle
