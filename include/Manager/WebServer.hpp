#pragma once
#include "../global.hpp"

namespace WebServer_Manager {
class WS {
 private:
  AsyncWebServer *ws;
  //   AsyncWebServer mWebServer;

 public:
  WS(/* args */);
  ~WS();
  void Begin();
};

WS::WS() {
  // ws = new AsyncWebServer(WEB_SERVER_PORT);
  // ws->on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", "Hello THERE!"); });
  // ws->begin();
  // setup
  //   AsyncWebServer mWebServer(WEB_SERVER_PORT);
  //   mWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", "Hello THERE!"); });
  //   mWebServer.begin();
}

WS::~WS() {}

void WS::Begin() {}

}  // namespace WebServer_Manager
