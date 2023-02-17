#pragma once
#include "../global.hpp"

namespace R_Comet {

void Draw() {
  const byte fadeAmt = 50;
  const int cometSize = 5;
  const int deltaHue = 4;
  const double cometSpeed = 0.8;

  static byte hue = HUE_RED;
  static int iDirection = 1;
  static double iPos = 0.0;

  hue += deltaHue;
  iPos += iDirection * cometSpeed;

  // Flip comet direction when it hits either end
  if (iPos >= (NUM_LEDS - cometSize) || iPos <= 0) {
    iDirection *= -1;
  }

  // Fade half the pixels
  for (int j = 0; j < NUM_LEDS; j++) {
    if (random(2) == 1) g_LEDs[j] = g_LEDs[j].fadeToBlackBy(fadeAmt);
  }

  // Draw comet at current position
  for (int i = 0; i < cometSize; i++) {
    g_LEDs[(int)iPos + i].setHue(hue);
  }
}

}  // namespace R_Comet