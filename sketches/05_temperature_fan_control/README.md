# 05 Temperature Fan Control

Mini project with an NTC sensor, one LED, and a fan.

## Goal
- Read temperature from an NTC on `A0`
- Convert the analog value to Celsius
- Turn the fan on and off with hysteresis
- Mirror the fan state with an LED on `Pin 6`

## Pins
- `A0`: NTC voltage divider
- `6`: status LED
- `10`: fan control

## Control Logic
- Target temperature: `20.0 C`
- Hysteresis: `0.5 C`
- Fan on above `20.5 C`
- Fan off below `19.5 C`

## Notes
- The code keeps a `fanOn` state so the fan does not flicker.
- Temperature is printed to the serial monitor every 2 seconds.
