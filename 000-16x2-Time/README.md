# Time

This Arduino sketch displays 24-hour time (Military time) and Desamber time on a 16 character by 2 line display.

It includes buttons to set the time. One button adds an hour, the other adds a minute.

Desamber is a time format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `Open Smart I2C / IIC LCD 1602 Display Module` and two `Momentary buttons`. This sketch does not use a `RTC (real-time clock)`, the time is instead set via the buttons.

<img src='https://raw.githubusercontent.com/kormyen/Ardusamber/master/000-16x2-Time/PREVIEW.jpg' width="600"/>


## Guide

### Wiring for LCD

- GND to GND
- VCC to 5V
- SDA to Analog 4
- ​SCL to Analog 5

### Wiring for buttons

- Hour button - wire one side to Arduino GND and the other to pin 7.
- Minute button - wire one side to Arduino GND and the other to pin 6.

### Setup

- Connect your Arduino to your PC with a USB cable
- Open and configure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) for your Arduino
- Open the `.ino` sketch that is in this directory
- Upload the sketch to your Arduino

### Usage

- Press the buttons until time is correct
- Enjoy


## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) to control the LCD and [TimeLib](https://github.com/PaulStoffregen/Time) for time manipulation.