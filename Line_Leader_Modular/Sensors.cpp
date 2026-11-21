#include "Config.h"
#include <EEPROM.h>
#include "RobotData.h"
#include "Sensors.h"
#include "Debug.h"

void selectMuxChannel(byte channel) {
  digitalWrite(MUX_S0, bitRead(channel, 0));
  digitalWrite(MUX_S1, bitRead(channel, 1));
  digitalWrite(MUX_S2, bitRead(channel, 2));
  digitalWrite(MUX_S3, bitRead(channel, 3));
}

void readSensors() {
  for (int i = 0; i < SENSOR_COUNT; i++) {
    selectMuxChannel(i);
    delayMicroseconds(5);
    (void)analogRead(MUX_SIG); // dummy read for ADC settling
    sensorRaw[i] = analogRead(MUX_SIG);
  }
}

void loadCalibration() {
  EEPROM.get(0, calibration);
  DBG_PRINT(F("[DBG][CAL] Citit din EEPROM (magic=0x"));
  DBG_PRINTLN(String(calibration.magic, HEX));

  if (calibrationValid()) {
    DBG_PRINTLN(F("[DBG][CAL] Calibrare EEPROM valida."));
    printCalibrationSummary();
  } else {
    DBG_PRINTLN(F("[DBG][CAL] Calibrare EEPROM invalida sau lipsa."));
  }
}

bool calibrationValid() {
  if (calibration.magic != EEPROM_MAGIC_VALUE) return false;

  for (int i = 0; i < SENSOR_COUNT; i++) {
    if (calibration.maxValues[i] - calibration.minValues[i] < MIN_CALIBRATION_SPAN) {
      return false;
    }
  }
  return true;
}

bool calibrateSensors() {
  DBG_PRINTLN(F("[DBG][CAL] Incepe calibrarea senzorilor (5000 ms)..."));

  for (int i = 0; i < SENSOR_COUNT; i++) {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }

  const unsigned long startTime = millis();
  while (millis() - startTime < CALIBRATION_DURATION_MS) {
    readSensors();
    for (int i = 0; i < SENSOR_COUNT; i++) {
      if (sensorRaw[i] < sensorMin[i]) sensorMin[i] = sensorRaw[i];
      if (sensorRaw[i] > sensorMax[i]) sensorMax[i] = sensorRaw[i];
    }
  }

  for (int i = 0; i < SENSOR_COUNT; i++) {
    const int span = sensorMax[i] - sensorMin[i];
    if (span < MIN_CALIBRATION_SPAN) {
      DBG_PRINT(F("[DBG][CAL][ERR] Senzorul "));
      DBG_PRINT(i);
      DBG_PRINT(F(" are span prea mic: "));
      DBG_PRINT(span);
      DBG_PRINT(F(" (min="));
      DBG_PRINT(sensorMin[i]);
      DBG_PRINT(F(", max="));
      DBG_PRINT(sensorMax[i]);
      DBG_PRINTLN(F(")"));
      return false;
    }
  }

  calibration.magic = EEPROM_MAGIC_VALUE;
  for (int i = 0; i < SENSOR_COUNT; i++) {
    calibration.minValues[i] = sensorMin[i];
    calibration.maxValues[i] = sensorMax[i];
  }

  EEPROM.put(0, calibration);
  DBG_PRINTLN(F("[DBG][CAL] Calibrare reusita si salvata in EEPROM."));
  printCalibrationSummary();
  return true;
}

void normalizeSensors() {
  for (int i = 0; i < SENSOR_COUNT; i++) {
    const int minimum = calibration.minValues[i];
    const int maximum = calibration.maxValues[i];
    const int range = maximum - minimum;

    if (range <= 0) {
      sensorValue[i] = 0;
      continue;
    }

    int value = map(sensorRaw[i], minimum, maximum, 0, 1000);
    value = constrain(value, 0, 1000);
    if (!BLACK_IS_HIGH) value = 1000 - value;
    sensorValue[i] = value;
  }
}

void calculateLinePosition() {
  long weightedSum = 0;
  long totalValue = 0;
  lineDetected = false;

  for (int i = 0; i < SENSOR_COUNT; i++) {
    const int value = sensorValue[i];
    if (value > SENSOR_THRESHOLD) lineDetected = true;
    weightedSum += (long)value * i * 1000L;
    totalValue += value;
  }

  if (totalValue > 0) linePosition = weightedSum / totalValue;
}
