# Clock

This Arduino sketch displays Desamber clock, date and time on a 128x128 ILI9163C screen.

Desamber is a time/date format created by [Devine Lu Linvega](https://github.com/neauoire). More information about Desamber [here](https://wiki.xxiivv.com/#clock).

This experiment was built with an `Arduino Uno`, an `1.44" Red Serial 128X128 SPI Color TFT LCD Display Module`. This sketch will use a `RTC (real-time clock)` soon, I need some batteries first.

## Guide

### Wiring for LCD

- VCC to 5V
- GND to GND
- CS to 10
- RESET to 9
- A0 to 8
- SDA to 11
- ​SCK to 13
- LED to 3.3V

### Setup

- Connect your Arduino to your PC with a USB cable
- Open and configure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) for your Arduino
- Open the `.ino` sketch that is in this directory
- Upload the sketch to your Arduino

### Usage

- Enjoy


## Dependencies

The code makes use of the [TFT_ILI9163C](https://github.com/sumotoy/TFT_ILI9163C) to control the LCD and [TimeLib](https://github.com/PaulStoffregen/Time) for timekeeping functionality.