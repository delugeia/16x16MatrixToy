#pragma once
#include "../global.hpp"

namespace ButtonManager {
class Button {
 private:
  uint8_t mPin;                     // GPIO PIN number for the button
  bool mStatus;                     // current HIGH/LOW status for the button
  bool mLastStatus;                 // status on previous update
  long mCount = 0;                  // number of times button was pressed
  unsigned long mPressStarted = 0;  // millis() when the button was pressed
  unsigned long mPressEnded = 0;    // millis() when the button was released
  unsigned long mPressTime = 0;     // total time in MS the button was pressed
  bool mPressedValue = HIGH;        // whether "HIGH" or "LOW" means it is being pressed
  bool mWasPressed = false;         // set when pressed, clear when checked with wasPressed()

 public:
  Button(uint8_t gpio_pin, bool pressedValue);
  Button(uint8_t gpio_pin) : Button(gpio_pin, HIGH){};
  ~Button(){};
  uint8_t getPin();
  bool update();
  bool getStatus();
  unsigned long getTime();
  bool isPressed() { return (mStatus == mPressedValue); };
  bool isNotPressed() { return (mStatus != mPressedValue); };
  bool wasPressed();
};

Button::Button(uint8_t gpio_pin, bool pressedValue) {
  mPin = gpio_pin;
  pinMode(mPin, INPUT);
  mStatus = digitalRead(mPin);
  mLastStatus = mStatus;
}

bool Button::update() {
  mStatus = digitalRead(mPin);
  if (mStatus != mLastStatus) {
    if (mStatus == mPressedValue) {
      mPressStarted = millis();
      mWasPressed = true;
    } else {
      mPressEnded = millis();
      mPressTime = mPressEnded - mPressStarted;
    }
    mLastStatus = mStatus;
  }
  return mStatus;
}

uint8_t Button::getPin() { return mPin; }

bool Button::getStatus() { return mStatus; }

unsigned long Button::getTime() {
  if (mStatus == mPressedValue) {
    return (millis() - mPressStarted);
  } else {
    return (mPressEnded - mPressStarted);
  }
}

// clear mWasPressed after reporting its state
bool Button::wasPressed() {
  if (mWasPressed) {
    mWasPressed = false;
    return true;
  } else {
    return false;
  }
}

/* **************************************************************
ButtonList - working on multiple buttons under one update
Button::Button *buttonA;
buttonA = buttonList.add(BUTTON_PIN_A);
*/
class ButtonList {
 private:
  Button *buttonList[255];
  uint8_t buttonCount = 0;

 public:
  ButtonList(){};
  ~ButtonList(){};
  Button *add(uint8_t gpio);
  void update();
};

Button *ButtonList::add(uint8_t gpio) {
  buttonList[buttonCount++] = new Button(gpio);
  return buttonList[buttonCount - 1];
}

void ButtonList::update() {
  for (int i = 0; i < buttonCount; i++) {
    buttonList[i]->update();
  }
}

}  // namespace Button