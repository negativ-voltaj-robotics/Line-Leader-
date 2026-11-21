#pragma once

// =====================================================
// LINE LEADER - HARDWARE AND TUNING CONFIGURATION
// Board: Arduino Nano
// =====================================================

// Debug
#define DEBUG_MODE true
#define DEBUG_BAUD 115200UL
#define DEBUG_PRINT_INTERVAL_MS 100UL

// 16-channel analog multiplexer
#define MUX_SIG A0
#define MUX_S0 2
#define MUX_S1 4
#define MUX_S2 8
#define MUX_S3 12
#define SENSOR_COUNT 16

// TB6612FNG
#define PWMA 3
#define AIN1 5
#define AIN2 6
#define PWMB 11
#define BIN1 7
#define BIN2 13
#define STBY A3

// Button and ESC
#define BUTTON_PIN 10
#define ESC_PIN 9

// Sensor configuration
#define BLACK_IS_HIGH true
#define SENSOR_THRESHOLD 250

// ESC configuration (microseconds)
#define ESC_MIN_US 1000
#define ESC_INIT_US 1800
#define ESC_RUN_US 1800
#define ESC_RAMP_STEP 10
#define ESC_RAMP_INTERVAL_MS 25UL

// PID tuning - edit these values when tuning the robot
#define PID_KP 2.8f
#define PID_KI 0.0002f
#define PID_KD 1.4f
#define PID_BASE_SPEED 60
#define PID_MAX_SPEED 100

// Calibration
#define EEPROM_MAGIC 0x4C4C
#define MIN_CALIBRATION_SPAN 30
#define CALIBRATION_DURATION_MS 5000UL
