#pragma once
#include "../global.hpp"

namespace R_SquareMarquee {

static uint8_t delta = NUM_LEDS_X / 2 - 1;

void Draw() {
  fadeToBlackBy(g_LEDs, NUM_LEDS, 96);
  for (auto x = delta; x < NUM_LEDS_X - delta; x++) {
    g_LEDs[XY(x, delta)] = CHSV(random8(255), 255, 255);
    g_LEDs[XY(x, NUM_LEDS_Y - 1 - delta)] = CHSV(random8(255), 255, 255);
  }
  for (auto y = delta; y < NUM_LEDS_Y - delta; y++) {
    g_LEDs[XY(delta, y)] = CHSV(random8(255), 255, 255);
    g_LEDs[XY(NUM_LEDS_X - 1 - delta, y)] = CHSV(random8(255), 255, 255);
  }

  if (delta == 0) {
    delta = NUM_LEDS_X / 2 - 1;
  }else{
    delta--;
  }
}

}  // namespace Routine_SquareMarquee
