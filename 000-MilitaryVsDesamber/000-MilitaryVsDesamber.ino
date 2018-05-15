/*
This Arduino sketch displays 24-hour time (Military time) and Desamber time.
It includes a button to add an hour, and a button to add a minute for time setting.
Desamber is a time format created by Devine Lu Linvega. More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <RBD_Button.h>

// PINS
#define BUTTON_PIN_HOUR 7
#define BUTTON_PIN_MINUTE 6

// LCD OFFSETS
#define ROW_OFFSET_ZERO 4 // Starting offset for text on first row of LCD 
#define ROW_OFFSET_ONE 5 // Starting offset for text on second row of LCD

// LCD
LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

// BUTTONS
RBD::Button buttonHour(BUTTON_PIN_HOUR); // Button for time adjust add hour
RBD::Button buttonMinute(BUTTON_PIN_MINUTE); // Button for time adjust add minute

// SHARED VARIABLES
int _hour = 0;
int _minute = 0;
int _second = 0;
unsigned long _milli = 0;

// MILLI OFFSET VARIABLES
unsigned long _milliOffset = 0;
int _hourPrev = 0;
int _minutePrev = 0;

void setup()
{
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();

  // Set initial millis offset. If this is not done dTime calc goes over 999:999 at 23:59.
  _milliOffset = millis();
}

void loop()
{
  // SHARED VARIABLES
  _hour = hour();
  _minute = minute();
  _second = second();
  _milli = millis();
  calcMilliOffset();

  // BUTTONS
  if(buttonHour.isPressed()) 
  {
    adjustTime(3600);
  }
  if(buttonMinute.isPressed()) 
  {
    adjustTime(60);
  }

  // Print 24-hour time to LCD
  writeToScreen(getMilitaryTime(), ROW_OFFSET_ZERO, 0);

  // Print Desamber time to LCD
  writeToScreen(getDesamberTime(), ROW_OFFSET_ONE, 1);

  delay(86); // '...the shortest pulse equals to 8.64 milliseconds...'
}

/// On rollover from midnight, Arduino millis are not reset we need to account for this - the Desamber calc uses millis.
/// There might still be a problem if the clock is kept running for 49 days as Arduino's millis() will rollover to zero... TODO!
void calcMilliOffset()
{
  if (_hour == 0 && _hourPrev == 23 && _minute == 0 && _minutePrev == 59)
  {
    // The time just went from 11pm to 12am.
    _milliOffset = millis();
  }
  _hourPrev = _hour;
  _minutePrev = _minute;
}

void writeToScreen(String value, int posX, int posY)
{
  lcd.setCursor(posX, posY);
  lcd.print(value);
}

String getMilitaryTime()
{
  String milTime = addMissingDigits(String(_hour), 2);
  milTime += ':';
  milTime += addMissingDigits(String(_minute), 2);
  milTime += ':';
  milTime += addMissingDigits(String(_second), 2);

  return milTime;
}

String getDesamberTime()
{
  // Calculate Desamber time
  unsigned long _dTime = (_hour * 3600000 + _minute * 60000 + _milli - _milliOffset) / 86.4;

  // Format to string with filler zero characters up to six total characters
  String _dTimeString = addMissingDigits(String(_dTime), 6);

  // Add ':' seperator between beat and pulse 
  return insertString(_dTimeString, ":", 3);
}

String addMissingDigits(String value, int totalDigits)
{
  int missingDigits = totalDigits - value.length();
  String result = "";
  
  for (int i = 0; i < missingDigits; i++){
    result += "0";
  }
  
  result += value;
  return result;
}

String insertString(String value, String addition, int indexPos)
{
  String result = value.substring(0, indexPos);
  result += addition;
  result += value.substring(indexPos, value.length());;
  return result;
}

