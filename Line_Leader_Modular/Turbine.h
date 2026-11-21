#pragma once
#include <Arduino.h>

extern bool escInitialized;
extern bool escEnabled;
extern int escTargetUs;
extern int escCurrentUs;

void setupESC();
void setESCThrottle(int targetUs);
void updateESC();
void stopESC();
