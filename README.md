# LINE LEADER
### Modular Autonomous Line Following Robot

LINE LEADER is an autonomous line-following robotics project developed around an Arduino Nano. It combines embedded programming, electronics, sensor processing and mechanical engineering to create a precise and configurable robotic platform.

The robot uses a 16-channel infrared sensing system, built from two sensor bars connected through a multiplexer. This configuration allows individual sensor readings to be processed by the microcontroller to determine line position and calculate steering corrections.

Movement is controlled by two DC motors through a TB6612FNG motor driver, using a configurable PID algorithm with adjustable proportional, integral and derivative parameters. The firmware also includes sensor calibration, EEPROM data storage and real-time serial debugging.

One of the project's additional features is an ESC-controlled turbine system with a configurable acceleration ramp. This adds another control subsystem to the robot and provides opportunities for further hardware and firmware optimization.

The software is organized into independent modules, separating PID control, sensor processing, motor management, turbine control, calibration, button handling and debugging. This modular architecture makes the firmware easier to understand, maintain, test and expand.

The robot operates through a four-stage state machine: IDLE, INITIALIZATION, READY and RUNNING, providing an organized startup and operating sequence.

LINE LEADER is an ongoing engineering project focused on improving autonomous navigation, control precision, hardware integration and embedded software architecture.

**Technologies:** Arduino Nano, C++, PID Control, Infrared Sensors, Multiplexer, TB6612FNG, ESC, EEPROM and Embedded Systems.

**LINE LEADER – Engineering precision into motion.**
