#pragma once
#include "../global.hpp"
#include "Matrix_Tables.hpp"


#ifdef MATRIX_TABLE_IS_UNDEFINED
uint16_t XY(uint16_t x, uint16_t y) { return (y * NUM_LEDS_X) + x; }
#else
uint16_t XY(uint16_t x, uint16_t y) { return XYTable[(y * NUM_LEDS_X) + x]; }
#endif

uint16_t RC(uint16_t row, uint16_t col) { return XY(col, row); }

bool isValidXY(int x, int y) { return (0 <= x && x < NUM_LEDS_X && 0 <= y && y < NUM_LEDS_Y); }