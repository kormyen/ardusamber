# Military vs Desamber

This Arduino sketch displays YY-MM-DD date format and Desamber date format on a 16 character by 2 line display.

It includes buttons to set the date. One button adds a year, one adds a month, one adds a day and one subtracks a day.

Desamber is a time/date format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `Open Smart I2C / IIC LCD 1602 Display Module` and four `Momentary buttons`. This sketch does not use a `RTC (real-time clock)`, the date is instead set via the momentary buttons.


## Guide

### Wiring for LCD

- GND to GND
- VCC to 5V
- SDA to Analog 4
- ​SCL to Analog 5

### Wiring for buttons

- Year button - wire one side to Arduino GND and the other to pin 7.
- Month button - wire one side to Arduino GND and the other to pin 6.
- Day add button - wire one side to Arduino GND and the other to pin 5.
- Day minus button - wire one side to Arduino GND and the other to pin 4.

### Usage

- Upload code with [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- Connect power to your Arduino
- Press buttons until date is correct
- Enjoy


## Dependencies

The code makes use of the [LiquidCrystal_I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) to control the LCD, [TimeLib](https://github.com/PaulStoffregen/Time) for timekeeping functionality and [RBD_Button](https://github.com/alextaujenis/RBD_Button) for simplified button handling.