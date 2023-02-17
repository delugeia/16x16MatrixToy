#pragma once
#define PRODUCTION_ENV true

// WiFi & WiFiManager
#define WIFI_SSID "***********"  // not used with WiFi Manager
#define WIFI_PASS "***********"  // not used with WiFi Manager
#define WEB_SERVER_PORT 80       // WebServer Default Port
#define WIFI_TIMEOUT 3000        // milliseconds to connect to WiFi
#define REBOOT_TIMEOUT 3

// FastLED
#define FASTLED_INTERNAL
#define LED_CHIPSET WS2812B
#define LED_COLOR_ORDER GRB
#define LED_PIN 23

#define NUM_LEDS_X 16                       // Number of LEDS in X-Dimension (Columns)
#define NUM_LEDS_Y 16                       // Number of LEDS in Y-Dimension (Rows)
#define NUM_LEDS (NUM_LEDS_X * NUM_LEDS_Y)  // Total number of LEDs

#define BRIGHTNESS_MIN 0    // Minimum Brightness
#define BRIGHTNESS 32       // Default Brightness
#define BRIGHTNESS_MAX 196  // Maximum Brightness

#define POWER_VOLTS 5                             // Power in Volts (e.g. 5 volts)
#define POWER_MA 2500                             // Power in Milliamps (10 A = 10,000 MA)
#define MAX_POWER_IN_MW (POWER_VOLTS * POWER_MA)  // Maximum LED power draw in milliwatts

// Controller
#define MS_DELAY 50      // Milliseconds between reads
#define BUTTON_PIN_A 39  // LEFT Button
#define BUTTON_PIN_B 36  // RIGHT Button
#define POT_PIN_A 34     // LEFT Potentiometer
#define POT_PIN_B 35     // RIGHT Potentiometer
#define MAX_FPS 130      // upper range of Frames Per Second via POT value

// Utility / Macros
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
