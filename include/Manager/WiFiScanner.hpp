#pragma once
#include "../global.hpp"

void WiFiScan () {

Serial.println("scan start");

// WiFi.scanNetworks will return the number of networks found
int n = WiFi.scanNetworks();
Serial.println("scan done");
if (n == 0) {
  Serial.println("no networks found");
} else {
  Serial.print(n);
  Serial.println(" networks found");
  for (int i = 0; i < n; ++i) {
    // Print SSID and RSSI for each network found
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(")");
    Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    delay(10);
  }
}
Serial.println("");

// Wait a bit before scanning again
delay(60000);

}