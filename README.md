# Arduino-Projects

Arduino learning repository for CPS basics, sensor/actuator exercises, and small exam-oriented mini projects.

## Focus
- Build practical Arduino skills step by step
- Connect theory with breadboard-based CPS exercises
- Keep each sketch small, testable, and easy to explain in class or exam review

## Featured Sketch
### 05 Temperature Fan Control
Mini CPS project with an NTC sensor, one LED, and a fan.

- Reads temperature from an NTC on `A0`
- Converts the analog input to Celsius
- Uses hysteresis to avoid unstable switching
- Turns on a fan and status LED when the threshold is exceeded

Files:
- `sketches/05_temperature_fan_control/05_temperature_fan_control.ino`
- `sketches/05_temperature_fan_control/README.md`

## Repository Structure
- `sketches/`: focused Arduino programs
- `lib/`: reusable helper libraries
- `docs/`: wiring notes, troubleshooting, learning summaries
- `assets/`: photos and circuit captures
- `test/`: optional host-side checks or simulation helpers

## Learning Path
1. `01_blink`: basic output and timing
2. `02_button_led`: digital input and LED control
3. `03_pwm_breathing`: PWM and smooth brightness control
4. `04_RGB`: multi-channel LED control
5. `05_temperature_fan_control`: sensor + actuator control with hysteresis

## Quick Start
1. Open Arduino IDE.
2. Open one folder under `sketches/`.
3. Select the board and serial port.
4. Verify and upload.
5. Use the serial monitor when the sketch logs sensor values.

## Current Direction
- CPS practice with sensors and actuators
- Arduino exercises connected to school lessons
- Small projects that can later be documented in `IT-Learning-Journey`
