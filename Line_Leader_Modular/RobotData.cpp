#include "Config.h"
#include "RobotData.h"

int sensorRaw[SENSOR_COUNT] = {0};
int sensorValue[SENSOR_COUNT] = {0};
int sensorMin[SENSOR_COUNT] = {0};
int sensorMax[SENSOR_COUNT] = {0};

int linePosition = 7500;
bool lineDetected = false;

float Kp = PID_KP;
float Ki = PID_KI;
float Kd = PID_KD;
int baseSpeed = PID_BASE_SPEED;
int maxSpeed = PID_MAX_SPEED;

float error = 0;
float previousError = 0;
float integral = 0;
unsigned long previousTime = 0;

CalibrationData calibration = {};
const uint16_t EEPROM_MAGIC_VALUE = EEPROM_MAGIC;

RobotState state = IDLE;

bool lastReading = HIGH;
bool stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long lastDebugPrintTime = 0;
