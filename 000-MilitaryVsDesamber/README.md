# Military vs Desamber

This Arduino sketch displays 24-hour time (Military time) and Desamber time on a 16 character by 2 line display.

It includes buttons to set the time. One button adds an hour, the other adds a minute.

Desamber is a time format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `Open Smart I2C / IIC LCD 1602 Display Module` and two `Momentary buttons`. This sketch does not use a `RTC (real-time clock)`, the time is instead set via the momentary buttons.

## Guide

- Press buttons until time is correct
- Enjoy

### Wiring for LCD

- GND to GND
- VCC to 5V
- SDA to Analog 4
- ​SCL to Analog 5

## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) to control the LCD, [TimeLib](https://github.com/PaulStoffregen/Time) for timekeeping functionality and [RBD_Button](https://github.com/alextaujenis/RBD_Button) for simplified button handling.