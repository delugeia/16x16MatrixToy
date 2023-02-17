#pragma once
#include "../global.hpp"

namespace R_Cylon {

void Draw() {
  static double rad = 0.00;
  static int xStart = 0;
  static int hue = 0;
  static float sinZeroToOne = 0;

  const int width = 2;
  const double radStep = 0.1;

  sinZeroToOne = (sin(rad) + 1.0) / 2.0;
  xStart = sinZeroToOne * (NUM_LEDS_X + 1 - width);
  hue = sinZeroToOne * 256;
  rad += radStep;

  fadeToBlackBy(g_LEDs, NUM_LEDS, 64);

  for (int xPos = xStart; xPos < xStart + width; xPos++) {
    for (auto yPos = 0; yPos < NUM_LEDS_Y; yPos++) {
      g_LEDs[XY(xPos, yPos)] = CHSV(hue, 255, 255);
    }
  }
}

}  // namespace Cylon
