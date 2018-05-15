# Military vs Desamber

This is a simple example Arduino sketch that displays 24-hour time (Military time) and Desamber time.

Desamber is a time format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This was built with an `Arduino Uno` and an `Open Smart I2C / IIC LCD 1602 Display Module`. This example does not use a `RTC (real-time clock)`, the start time is instead set via code.

<img src='https://raw.githubusercontent.com/kormyen/ArduinoDesamber/master/000-MilitaryVsDesamber/PREVIEW.jpg' width="600"/>

## Guide

To set the start time change the 'setTime' line in setup(): [`setTime(hr,min,sec,day,month,yr);`](https://github.com/PaulStoffregen/Time)

### Wiring for LCD

- GND to GND
- VCC to 5V
- SDA to Analog 4
- ​SCL to Analog 5

## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) and [TimeLib](https://github.com/PaulStoffregen/Time) libraries.