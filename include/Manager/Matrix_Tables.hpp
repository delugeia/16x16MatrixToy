#pragma once
#include "../global.hpp"

#if ((NUM_LEDS_X == 16) && (NUM_LEDS_Y == 16))
// 16 x 16 "Flexible" board from AdaFruit
const uint8_t XYTable[] = {
    // rows of coordinates
    0,  31, 32, 63, 64, 95, 96,  127, 128, 159, 160, 191, 192, 223, 224, 255,   // ROW
    1,  30, 33, 62, 65, 94, 97,  126, 129, 158, 161, 190, 193, 222, 225, 254,   // ROW
    2,  29, 34, 61, 66, 93, 98,  125, 130, 157, 162, 189, 194, 221, 226, 253,   // ROW
    3,  28, 35, 60, 67, 92, 99,  124, 131, 156, 163, 188, 195, 220, 227, 252,   // ROW
    4,  27, 36, 59, 68, 91, 100, 123, 132, 155, 164, 187, 196, 219, 228, 251,   // ROW
    5,  26, 37, 58, 69, 90, 101, 122, 133, 154, 165, 186, 197, 218, 229, 250,   // ROW
    6,  25, 38, 57, 70, 89, 102, 121, 134, 153, 166, 185, 198, 217, 230, 249,   // ROW
    7,  24, 39, 56, 71, 88, 103, 120, 135, 152, 167, 184, 199, 216, 231, 248,   // ROW
    8,  23, 40, 55, 72, 87, 104, 119, 136, 151, 168, 183, 200, 215, 232, 247,   // ROW
    9,  22, 41, 54, 73, 86, 105, 118, 137, 150, 169, 182, 201, 214, 233, 246,   // ROW
    10, 21, 42, 53, 74, 85, 106, 117, 138, 149, 170, 181, 202, 213, 234, 245,   // ROW
    11, 20, 43, 52, 75, 84, 107, 116, 139, 148, 171, 180, 203, 212, 235, 244,   // ROW
    12, 19, 44, 51, 76, 83, 108, 115, 140, 147, 172, 179, 204, 211, 236, 243,   // ROW
    13, 18, 45, 50, 77, 82, 109, 114, 141, 146, 173, 178, 205, 210, 237, 242,   // ROW
    14, 17, 46, 49, 78, 81, 110, 113, 142, 145, 174, 177, 206, 209, 238, 241,   // ROW
    15, 16, 47, 48, 79, 80, 111, 112, 143, 144, 175, 176, 207, 208, 239, 240};  // ROW

#else
// undefined... just return an empty 1024 array
const uint16_t XYTable[1024] = {};
#define MATRIX_TABLE_IS_UNDEFINED

#endif