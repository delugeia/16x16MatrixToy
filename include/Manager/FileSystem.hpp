#pragma once
#include "../global.hpp"

namespace FS_Manager {

bool StartFS() {
  bool result = SPIFFS.begin(true);
  return result;
}

String ReadFile(const char *path) {
  String content;
  File file = SPIFFS.open(path);
  while (file.available()) {
    content += String((char)file.read());
  }
  file.close();
  return content;
}

bool WriteFile(const char *path, const char *content) {
  File file = SPIFFS.open(path, FILE_WRITE);
  bool result = file.print(content);
  file.close();
  return result;
}

}  // namespace FS_Manager
