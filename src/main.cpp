#include "global.hpp"

CRGB g_LEDs[NUM_LEDS] = {0};

AsyncWebServer web(WEB_SERVER_PORT);
// WebServer_Manager::WS myWebServer;

void bootLED(uint led, CRGB color) {
  g_LEDs[led] = color;
  FastLED.show();
  delay(100);
}

void setup() {
  Serial.begin(115200);
  Serial.println("BEGIN");

  FastLED.addLeds<LED_CHIPSET, LED_PIN, LED_COLOR_ORDER>(g_LEDs, NUM_LEDS);
  FastLED.setMaxPowerInMilliWatts(MAX_POWER_IN_MW);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
  bootLED(0, CRGB::Green);

  bootLED(1, CRGB::Yellow);
  if (FS_Manager::StartFS()) bootLED(1, CRGB::Green);

  bootLED(2, CRGB::Yellow);
  if (g_Controler->Begin()) bootLED(2, CRGB::Green);

  bootLED(3, CRGB::Yellow);
  if (g_Controler->buttonA->isPressed()) {
    // Skip WiFi
    bootLED(3, CRGB::Red);
  } else if (g_Controler->buttonB->isPressed()) {
    bootLED(3, CRGB::Cyan);
    g_WiFi->Begin(true);  // Reset WiFi - Always call WiFiManager and Reboot
  } else {
    g_WiFi->Begin();  // Try WiFi - Call WiFiManager only if needed, if so then reboot
    bootLED(3, CRGB::Green);

    web.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", "Hello THERE!"); });
    web.begin();

    // g_WebServer.Begin();
  }

  delay(1000);
  FastLED.clear(true);
}

void loop() {
  static unsigned long lastShow = millis();
  static uint8_t routine = 0;
  static uint8_t totalRoutines = 3;
  static bool callReset = false;

  g_Controler->Update();

  EVERY_N_MILLIS(500) {
    if (g_Controler->buttonB->isPressed() && g_Controler->buttonA->isPressed() && (g_Controler->buttonB->getTime() > 3000) && !callReset) {
      callReset = true;
      Serial.printf("Resetting...!\n");
    }

    if (callReset) {
      fill_solid(g_LEDs, NUM_LEDS, CRGB::White);
      FastLED.show();
      delay(3000);
      g_Controler->Update();
      if (g_Controler->buttonB->isPressed() && g_Controler->buttonA->isPressed()) {
        // actually reset
        Serial.println("Guess We're Resetting!");
        for (uint i = 0; i < 50; i++) {
          Serial.printf("Red %3d : %3d\n", i, g_LEDs[0].red);
          fadeToBlackBy(g_LEDs, NUM_LEDS, 10);
          FastLED.show();
          delay(5);
        }
        FastLED.clear(true);
        delay(1000);
        ESP.restart();
      } else {
        callReset = false;
        FastLED.clear(true);
      }
    }
  }

  if (g_Controler->buttonA->wasPressed()) {
    FastLED.clear();
    routine = (routine + 1) % totalRoutines;
    Serial.printf("Changing Routine to %d\n", routine);
  }

  if (millis() - lastShow > g_Controler->showDelayMS) {
    lastShow = millis();

    switch (routine) {
      case 0:
        R_Cylon::Draw();
        break;

      case 1:
        R_SquareMarquee::Draw();
        break;

      case 2:
        R_Twinkle::Draw(g_Controler->buttonB->wasPressed());
        break;

      case 3:
        R_Comet::Draw();
        break;

      default:
        break;
    }

    FastLED.show(g_Controler->brightness);
  }
}