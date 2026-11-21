#include "Config.h"
#include "RobotData.h"
#include "Debug.h"
#include "Sensors.h"
#include "Motors.h"
#include "Turbine.h"
#include "Button.h"
#include "PID.h"

void setup() {
#if DEBUG_MODE
  Serial.begin(DEBUG_BAUD);
  const unsigned long serialStart = millis();
  while (!Serial && (millis() - serialStart < 1500UL)) {
    // Short wait for Serial Monitor; does not block indefinitely.
  }
  DBG_PRINTLN(F("=== LINE LEADER BOOT ==="));
#endif

  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  setupESC();
  stopMotors();
  stopESC();
  loadCalibration();

  state = IDLE;
  DBG_PRINT(F("[DBG][STATE] Stare initiala: "));
  DBG_PRINTLN(stateToString(state));
}

void loop() {
  // Keep the ESC ramp service running in every robot state.
  updateESC();

  if (buttonPressed()) {
    const RobotState previousState = state;

    switch (state) {
      case IDLE:
        // Click 1: calibrate sensors; turbine remains stopped.
        stopMotors();
        stopESC();
        if (calibrateSensors()) {
          state = INITIALIZATION;
        } else {
          DBG_PRINTLN(F("[DBG][STATE] Calibrarea a esuat -> ramane in IDLE."));
        }
        break;

      case INITIALIZATION:
        // Click 2: request initialization throttle; ramp is non-blocking.
        stopMotors();
        setESCThrottle(ESC_INIT_US);
        state = READY;
        break;

      case READY:
        // Click 3: request run throttle and start line following.
        setESCThrottle(ESC_RUN_US);
        resetPID();
        state = RUNNING;
        break;

      case RUNNING:
        // Click 4: stop drive motors and turbine, return to IDLE.
        stopMotors();
        stopESC();
        state = IDLE;
        break;
    }

    if (state != previousState) {
      DBG_PRINT(F("[DBG][STATE] "));
      DBG_PRINT(stateToString(previousState));
      DBG_PRINT(F(" -> "));
      DBG_PRINTLN(stateToString(state));
    }
  }

  if (state == RUNNING) {
    followLine();
  }
}
