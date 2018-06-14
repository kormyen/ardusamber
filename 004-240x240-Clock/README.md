# Clock

This `Arduino` sketch displays the `Desamber` [clock](https://wiki.xxiivv.com/#entaloneralie) `Entaloneralie`, [date](https://wiki.xxiivv.com/#calendar) and [time](https://wiki.xxiivv.com/#clock) on a 240x240 ST7789 screen.

It includes buttons to set the time. The first adds a mid beat, the second button adds a third beat, the third button adds a pulse.

This experiment was built with an `Arduino Uno`, a `1.3" 240x240 IPS Color TFT LCD Display Module` and three `Momentary buttons`. This sketch will use a `RTC (real-time clock)` soon, I need some batteries first.

***NOTE:** The 128x128 screen is actually better for this clock being physically larger and since it has four times fewer pixels it refreshes faster. `Entaloneralie` is all vertical and horizontal lines it doesn't benefit greatly from the increased resolution.*

## Wishlist

- Fix clock to be specified width (currently width + 1).
- Refactor drawClock method to receive dtime, x, y, size, containerThickness, needleThickness and doErase as parameters.
- Fix line erasing to no longer need refresh() hack when adjusting time faster than real time.
- Try optional dotted line (or similar) extending above second beat line.
- Try optional beat indicator numbers.
- Try fullscreen clock rendering (zero margin and no data or time).
- Pomodoro start/stop button.
- Simple live edge wooden case.

## Guide

### Wiring for LCD

- VCC to 5V
- GND to GND
- SCL to 13
- SDA to 11
- RESET to 9
- DC to 8
- BLK to ?

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

The code makes use of the [Arduino ST7789 Library](https://github.com/ananevilya/Arduino-ST7789-Library) and [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library/) to control the LCD and [TimeLib](https://github.com/PaulStoffregen/Time) for time manipulation.