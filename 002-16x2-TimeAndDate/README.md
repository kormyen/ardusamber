# Time and Date

This Arduino sketch displays four screens of different time and date formats on a 16 character by 2 line display.

The forth button changes mode.

The first three buttons change date/time on certain modes.

- The first mode `The time is` displays Desamber time.
- The second mode `Desamber` displays Desamber time and date.
- The third mode `Military` displays 24-hour time and YY-MM-DD.
- The forth mode `Time` displays Desamber time and 24-hour time. In this mode the first three buttons change time.
- The fifth mode `Date` displays the Desamber date and YY-MM-DD. In this mode the first three buttons change date.

Desamber is a time/date format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `Open Smart I2C / IIC LCD 1602 Display Module` and four `Momentary buttons`. This sketch does not use a `RTC (real-time clock)`, the date is instead set via the buttons.

<img src='https://raw.githubusercontent.com/kormyen/Ardusamber/master/002-16x2-TimeAndDate/PREVIEW.jpg' width="600"/>

## Guide

### Wiring for LCD

- GND to GND
- VCC to 5V
- SDA to Analog 4
- ​SCL to Analog 5

### Wiring for buttons

- First button - wire one side to Arduino GND and the other to pin 7.
- Second button - wire one side to Arduino GND and the other to pin 6.
- Third button - wire one side to Arduino GND and the other to pin 5.
- Mode button - wire one side to Arduino GND and the other to pin 4.

### Setup

- Connect your Arduino to your PC with a USB cable
- Open and configure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) for your Arduino
- Open the `.ino` sketch that is in this directory
- Upload the sketch to your Arduino

### Usage

- Press the forth button (mode) three times until 24-hour and Desamber times are displayed
- Press the first three buttons until time is correct (add hour, add minute, add second)
- Press mode button once more to show YY-MM-DD and Deasmber dates
- Press the first three buttons until date is correct (add year, add month, add day)
- Enjoy


## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) to control the LCD and [TimeLib](https://github.com/PaulStoffregen/Time) for time manipulation.