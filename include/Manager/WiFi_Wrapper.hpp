#pragma once
#include "../global.hpp"

namespace WiFi_Wrapper {
class WiFi_Wrapper {
 private:
  String mDNS = "esp32display";
  IPAddress localIPAddress;

 public:
  WiFi_Wrapper(/* args */){};
  ~WiFi_Wrapper(){};
  bool Begin(bool reset);
  void WiFiManagerCall(bool reset);
};

bool WiFi_Wrapper::Begin(bool reset = false) {
  mDNS = FS_Manager::ReadFile("/mDNS");

  WiFi.mode(WIFI_STA);
  WiFi.begin();

  uint timeoutBegin = millis();
  Serial.print(">> Connecting WiFi ");
  while ((WiFi.status() != WL_CONNECTED) && (millis() - timeoutBegin < WIFI_TIMEOUT)) {
    Serial.print(".");
    delay(50);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(">> Resetting WiFi - Connection Failed.");
    WiFiManagerCall(true);
  }

  localIPAddress = WiFi.localIP();
  Serial.println(">> WiFi Connected");

  Serial.printf(">> Registering mDNS (%s.local)\n", mDNS.c_str());
  if (!MDNS.begin(mDNS.c_str())) {
    Serial.println(">> Error starting mDNS\n");
  } else {
    MDNS.addService("http", "tcp", 80);
    Serial.println(">> mDNS Registered\n");
    Serial.println(">> http://" + mDNS + ".local/");
  }
  Serial.printf(">> http://%s/\n", localIPAddress.toString());

  return true;
}

void WiFi_Wrapper::WiFiManagerCall(bool reset) {
  WiFiManager wm;

  wm.setDebugOutput(true, "\t\t *wm: ");
  wm.setShowPassword(true);
  wm.setConnectTimeout(3);

  if (reset) {
    Serial.println("Resetting...\n");
    wm.resetSettings();
  } else {
    Serial.println("NOT Resetting...\n");
  }

  WiFiManagerParameter q_mDNS("q_mDNS", "Choose NAME.local web address", "esp32display", 50);
  wm.addParameter(&q_mDNS);

  bool connectResult = wm.autoConnect("ESP WFM");  // anonymous ap

  if (!connectResult) {
    Serial.println("Failed to connect");
    delay(3000);
    // ESP.restart();
  } else {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  Serial.println("Connected.\n");
  Serial.printf("You Entered: [%s]\n\n", q_mDNS.getValue());

  FS_Manager::WriteFile("/mDNS", q_mDNS.getValue());

  Serial.println("\n\nWiFiManager DONE.");

  Serial.print("\n\nREBOOTING IN:");
  for (int i = 0; i < REBOOT_TIMEOUT; i++) {
    Serial.printf(" %d...", REBOOT_TIMEOUT - i);
    delay(1000);
  }
  Serial.println(" 0.\n\nRebooting...");
  delay(100);

  ESP.restart();
}

}  // namespace WiFi_Wrapper