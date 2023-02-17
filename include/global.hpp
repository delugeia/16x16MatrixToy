#pragma once
#include "define.hpp"

#include <Arduino.h>
using namespace std;

#include <sys/time.h>
#include <string>
#include <vector>

#include <SPIFFS.h>
#include "Manager/FileSystem.hpp"

#include "Manager/Button.hpp"
#include "Manager/Control.hpp"
Control_Manager::Control *g_Controler = new Control_Manager::Control();

#include <FastLED.h>
extern CRGB g_LEDs[];

#include "Manager/Matrix.hpp"

#include "Routine/Comet.hpp"
#include "Routine/Cylon.hpp"
#include "Routine/SquareMarquee.hpp"
#include "Routine/Twinkle.hpp"
// BouncingBallEffect balls(NUM_LEDS, 3, 32, 4.0, true);

#include <ESPmDNS.h>  // https://youtu.be/WiIpKr6Fs1g https://techtutorialsx.com/2020/04/17/esp32-mdns-address-resolution/
#include <WiFi.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

#include "ESPAsyncWebServer.h"
#include "Manager/WebServer.hpp"
// WebServer_Manager::WS g_WebServer;

#include "Manager/WiFi_Wrapper.hpp"
WiFi_Wrapper::WiFi_Wrapper *g_WiFi = new WiFi_Wrapper::WiFi_Wrapper();
