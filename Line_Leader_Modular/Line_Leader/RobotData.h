#pragma once
#include <Arduino.h>
#include "Config.h"

struct CalibrationData {
  uint16_t magic;
  int minValues[SENSOR_COUNT];
  int maxValues[SENSOR_COUNT];
};

enum RobotState {
  IDLE,
  INITIALIZATION,
  READY,
  RUNNING
};

extern int sensorRaw[SENSOR_COUNT];
extern int sensorValue[SENSOR_COUNT];
extern int sensorMin[SENSOR_COUNT];
extern int sensorMax[SENSOR_COUNT];

extern int linePosition;
extern bool lineDetected;

extern float Kp;
extern float Ki;
extern float Kd;
extern int baseSpeed;
extern int maxSpeed;

extern float error;
extern float previousError;
extern float integral;
extern unsigned long previousTime;

extern CalibrationData calibration;
extern const uint16_t EEPROM_MAGIC_VALUE;

extern RobotState state;

extern bool lastReading;
extern bool stableButtonState;
extern unsigned long lastDebounceTime;
extern const unsigned long debounceDelay;

extern unsigned long lastDebugPrintTime;
