#include <Arduino.h>
#include "Config.h"
#include "Motors.h"
#include "Debug.h"

void setMotor(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, leftSpeed >= 0);
  digitalWrite(AIN2, leftSpeed < 0);
  analogWrite(PWMA, abs(leftSpeed));

  digitalWrite(BIN1, rightSpeed >= 0);
  digitalWrite(BIN2, rightSpeed < 0);
  analogWrite(PWMB, abs(rightSpeed));
}

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(STBY, LOW);
  DBG_PRINTLN(F("[DBG][MOT] Motoare oprite (STBY=LOW)."));
}
