#include <Arduino.h>
#include "Config.h"
#include "RobotData.h"
#include "Button.h"
#include "Debug.h"

bool buttonPressed() {
  const bool reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) lastDebounceTime = millis();

  bool pressed = false;
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != stableButtonState) {
      stableButtonState = reading;
      if (stableButtonState == LOW) {
        pressed = true;
        DBG_PRINTLN(F("[DBG][BTN] Apasare buton detectata (LOW)."));
      }
    }
  }

  lastReading = reading;
  return pressed;
}
