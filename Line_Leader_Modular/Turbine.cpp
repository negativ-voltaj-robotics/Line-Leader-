#include "Config.h"
#include <Servo.h>
#include "Turbine.h"
#include "Debug.h"

static Servo esc;
bool escInitialized = false;
bool escEnabled = false;
int escTargetUs = ESC_MIN_US;
int escCurrentUs = ESC_MIN_US;
static unsigned long lastEscRampTime = 0;

void setupESC() {
  esc.attach(ESC_PIN);
  escCurrentUs = ESC_MIN_US;
  escTargetUs = ESC_MIN_US;
  esc.writeMicroseconds(escCurrentUs);
  escInitialized = true;
  escEnabled = false;

  DBG_PRINT(F("[DBG][ESC] Atasat pe pin "));
  DBG_PRINT(ESC_PIN);
  DBG_PRINT(F(" cu semnal initial "));
  DBG_PRINT(ESC_MIN_US);
  DBG_PRINTLN(F(" us"));
}

void setESCThrottle(int targetUs) {
  escTargetUs = constrain(targetUs, ESC_MIN_US, 2000);
  escEnabled = (escTargetUs > ESC_MIN_US);

  DBG_PRINT(F("[DBG][ESC] Nou target setat: "));
  DBG_PRINT(escTargetUs);
  DBG_PRINT(F(" us (curent: "));
  DBG_PRINT(escCurrentUs);
  DBG_PRINTLN(F(" us)"));
}

void updateESC() {
  if (!escInitialized) return;

  const unsigned long now = millis();
  if (now - lastEscRampTime < ESC_RAMP_INTERVAL_MS) return;
  lastEscRampTime = now;

  const int previousUs = escCurrentUs;

  if (escCurrentUs < escTargetUs) {
    escCurrentUs += ESC_RAMP_STEP;
    if (escCurrentUs > escTargetUs) escCurrentUs = escTargetUs;
  } else if (escCurrentUs > escTargetUs) {
    escCurrentUs -= ESC_RAMP_STEP;
    if (escCurrentUs < escTargetUs) escCurrentUs = escTargetUs;
  }

  if (escCurrentUs != previousUs) {
    esc.writeMicroseconds(escCurrentUs);
    escEnabled = (escCurrentUs > ESC_MIN_US);

    if (escCurrentUs == escTargetUs) {
      DBG_PRINT(F("[DBG][ESC] Tinta atinsa: "));
      DBG_PRINT(escCurrentUs);
      DBG_PRINTLN(F(" us"));
    }
  }
}

void stopESC() {
  escEnabled = false;
  escTargetUs = ESC_MIN_US;
  escCurrentUs = ESC_MIN_US;
  if (escInitialized) esc.writeMicroseconds(ESC_MIN_US);
  DBG_PRINTLN(F("[DBG][ESC] Oprit (1000 us)"));
}
