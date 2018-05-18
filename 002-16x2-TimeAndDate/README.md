# Time and Date

This Arduino sketch displays four screens of different time and date formats on a 16 character by 2 line display.
The forth button changes mode.

The first mode displays Desamber time and date.
The second mode displays 24-hour time and YY-MM-DD.
The third mode displays Desamber time and 24-hour time. In this mode buttons one, two and three change the time.
The forth mode displays the Desamber date and YY-MM-DD. In this mode buttons one, two and three change the date.
Desamber is a time format created by Devine Lu Linvega. More information about Desamber here: https://wiki.xxiivv.com/#clock

Desamber is a time/date format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `Open Smart I2C / IIC LCD 1602 Display Module` and four `Momentary buttons`. This sketch does not use a `RTC (real-time clock)`, the date is instead set via the momentary buttons.

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

### Usage

- Upload code with [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- Connect power to your Arduino
- Press mode button (three times) until 24-hour and Desamber times are displayed
- Press buttons until time is correct (add year, add month, add day)
- Press mode button (once more) until YY-MM-DD and Deasmber dates are displayed
- Press buttons until date is correct (add hour, add minute, add second)
- Enjoy


## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) to control the LCD, [TimeLib](https://github.com/PaulStoffregen/Time) for timekeeping functionality and [RBD_Button](https://github.com/alextaujenis/RBD_Button) for simplified button handling.