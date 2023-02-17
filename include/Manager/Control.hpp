#pragma once
#include "../global.hpp"

namespace Control_Manager {

class Control {
 public:
  ButtonManager::Button *buttonA;
  ButtonManager::Button *buttonB;
  int brightness = BRIGHTNESS;
  int showDelayMS = 0;
  int potValueA = 0;
  int potValueB = 0;
  Control();
  void Update();
  bool Begin();
};

Control::Control() {
  buttonA = new ButtonManager::Button(BUTTON_PIN_A);
  buttonB = new ButtonManager::Button(BUTTON_PIN_B);
  pinMode(POT_PIN_A, INPUT);
  pinMode(POT_PIN_B, INPUT);
}

bool Control::Begin() {
  Update();
  return true;
}

void Control::Update() {
  buttonA->update();
  buttonB->update();

  potValueA = analogRead(POT_PIN_A);
  showDelayMS = 1000 / map(potValueA, 0, 4095, 1, MAX_FPS);

  potValueB = analogRead(POT_PIN_B);
  brightness = map(potValueB, 0, 4095, 1, BRIGHTNESS_MAX);
}

}  // namespace Control