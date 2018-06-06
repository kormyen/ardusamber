# Clock

This `Arduino` sketch displays the `Desamber` [clock](https://wiki.xxiivv.com/#entaloneralie), [date](https://wiki.xxiivv.com/#calendar) and [time](https://wiki.xxiivv.com/#clock) on a 128x128 ILI9163C screen.

It includes buttons to set the time. The first adds a mid beat, the second button adds a third beat, the third button adds a pulse.

This experiment was built with an `Arduino Uno`, a `1.44" Red Serial 128X128 SPI Color TFT LCD Display Module` and three `Momentary buttons`. This sketch will use a `RTC (real-time clock)` soon, I need some batteries first.

<img src='https://raw.githubusercontent.com/kormyen/Ardusamber/master/003-128x128-Clock/PREVIEWCLOSE.jpg' width="600"/>

<img src='https://raw.githubusercontent.com/kormyen/Ardusamber/master/003-128x128-Clock/PREVIEWGIF.gif' width="600"/>

<img src='https://raw.githubusercontent.com/kormyen/Ardusamber/master/003-128x128-Clock/PREVIEW.jpg' width="600"/>

## Wishlist

- Fix clock to be specified width (currently width + 1).
- Refactor drawClock method to receive dtime, x, y, size, containerLineThickness, clockLineThickness and doErase as parameters.
- Fix line erasing to no longer need refresh() hack when adjusting time faster than real time.
- Try optional dotted line (or similar) extending above second beat line.
- Try optional beat indicator numbers.
- Try fullscreen clock rendering.
- Pomodoro start/stop button.
- Simple live edge wooden case.  

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

### Wiring for buttons

- Mid beat button - wire one side to Arduino GND and the other to pin 2.
- Third beat button - wire one side to Arduino GND and the other to pin 3.
- Pulse button - wire one side to Arduino GND and the other to pin 4.

### Setup

- Connect your Arduino to your PC with a USB cable
- Open and configure the [Arduino IDE](https://www.arduino.cc/en/Main/Software) for your Arduino
- Open the `.ino` sketch that is in this directory
- Upload the sketch to your Arduino

### Usage

- Press the buttons until time is correct
- Enjoy


## Dependencies

The code makes use of the [TFT_ILI9163C](https://github.com/sumotoy/TFT_ILI9163C) and [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library/) to control the LCD and [TimeLib](https://github.com/PaulStoffregen/Time) for time manipulation.