#include "Config.h"
#include "Debug.h"
#include "Turbine.h"

const char* stateToString(RobotState s) {
  switch (s) {
    case IDLE: return "IDLE";
    case INITIALIZATION: return "INITIALIZATION";
    case READY: return "READY";
    case RUNNING: return "RUNNING";
    default: return "UNKNOWN";
  }
}

void printCalibrationSummary() {
#if DEBUG_MODE
  Serial.println(F("[DBG][CAL] Min / Max per senzor:"));
  for (int i = 0; i < SENSOR_COUNT; i++) {
    Serial.print(F("  S"));
    if (i < 10) Serial.print('0');
    Serial.print(i);
    Serial.print(F(": min="));
    Serial.print(calibration.minValues[i]);
    Serial.print(F(" max="));
    Serial.print(calibration.maxValues[i]);
    Serial.print(F(" span="));
    Serial.println(calibration.maxValues[i] - calibration.minValues[i]);
  }
#endif
}

void printLineTelemetry(int leftSpeed, int rightSpeed, float correction) {
#if DEBUG_MODE
  const unsigned long now = millis();
  if (now - lastDebugPrintTime < DEBUG_PRINT_INTERVAL_MS) return;
  lastDebugPrintTime = now;

  Serial.print(F("[DBG][PID] det="));
  Serial.print(lineDetected ? 1 : 0);
  Serial.print(F(" pos="));
  Serial.print(linePosition);
  Serial.print(F(" err="));
  Serial.print(error, 1);
  Serial.print(F(" corr="));
  Serial.print(correction, 1);
  Serial.print(F(" L="));
  Serial.print(leftSpeed);
  Serial.print(F(" R="));
  Serial.print(rightSpeed);
  Serial.print(F(" esc="));
  Serial.print(escCurrentUs);
  Serial.print('/');
  Serial.println(escTargetUs);
#endif
}
