  #include <Arduino.h>
#include "Config.h"
#include "RobotData.h"
#include "Sensors.h"
#include "Motors.h"
#include "Debug.h"
#include "PID.h"

void resetPID() {
  error = 0;
  previousError = 0;
  integral = 0;
  previousTime = micros();
}

void followLine() {
  readSensors();
  normalizeSensors();
  calculateLinePosition();

  if (!lineDetected) {
    stopMotors();
    printLineTelemetry(0, 0, 0);
    return;
  }

  error = linePosition - 7500;
  const unsigned long currentTime = micros();
  const float dt = (currentTime - previousTime) / 1000000.0f;

  if (dt <= 0 || dt > 0.1f) {
    previousTime = currentTime;
    return;
  }

  integral += error * dt;
  integral = constrain(integral, -10000, 10000);
  const float derivative = (error - previousError) / dt;

  const float correction = Kp * error + Ki * integral + Kd * derivative;
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
  rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

  setMotor(leftSpeed, rightSpeed);
  printLineTelemetry(leftSpeed, rightSpeed, correction);

  previousError = error;
  previousTime = currentTime;
}
