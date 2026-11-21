#pragma once
#include <Arduino.h>

void selectMuxChannel(byte channel);
void readSensors();
void loadCalibration();
bool calibrationValid();
bool calibrateSensors();
void normalizeSensors();
void calculateLinePosition();
