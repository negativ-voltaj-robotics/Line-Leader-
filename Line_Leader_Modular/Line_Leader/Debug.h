#pragma once
#include <Arduino.h>
#include "RobotData.h"

#if DEBUG_MODE
  #define DBG_PRINT(x) Serial.print(x)
  #define DBG_PRINTLN(x) Serial.println(x)
#else
  #define DBG_PRINT(x) do {} while (0)
  #define DBG_PRINTLN(x) do {} while (0)
#endif

const char* stateToString(RobotState s);
void printCalibrationSummary();
void printLineTelemetry(int leftSpeed, int rightSpeed, float correction);
