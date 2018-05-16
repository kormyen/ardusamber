/*
This Arduino sketch displays 24-hour time (Military time) and Desamber time.
It includes buttons to set the time. One button adds an hour, the other adds a minute.
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


class desamberTime
{
  public:
  String beat;
  String pulse;
  String formatted;

  String getTime(unsigned long hr, unsigned long minu, unsigned long sec, unsigned long mil)
  {
    // Calculate Desamber time
    unsigned long _dTime = ((hr * 3600000) + (minu * 60000) + (sec * 1000) + mil) / 86.4;

    // Format to string with filler zero characters up to six total characters
    String _dTimeString = addMissingDigits(String(_dTime), 6);
    
    beat = _dTimeString.substring(0, 3);
    pulse = _dTimeString.substring(3, 6);
    formatted = beat + ":" + pulse;

    return formatted;
  }

  String addMissingDigits(String value, int digitsRequired)
  {
    int missingDigits = digitsRequired - value.length();
    String result = "";
    
    for (int i = 0; i < missingDigits; i++)
    {
      result += "0";
    }
    
    result += value;
    return result;
  }
};


class militaryTime
{
  public:
  String formatted;

  String getTime(unsigned long hr, unsigned long minu, unsigned long sec, unsigned long mil)
  {
    String formatted = addMissingDigits(String(hr), 2);
    formatted += ':';
    formatted += addMissingDigits(String(minu), 2);
    formatted += ':';
    formatted += addMissingDigits(String(sec), 2);
    return formatted;
  }

  String addMissingDigits(String value, int digitsRequired)
  {
    int missingDigits = digitsRequired - value.length();
    String result = "";
    
    for (int i = 0; i < missingDigits; i++)
    {
      result += "0";
    }
    
    result += value;
    return result;
  }
};


// LCD
LiquidCrystal_I2C lcd(0x20,16,2);  // Set the LCD address to 0x20 for a 16 chars and 2 line display

// BUTTONS
RBD::Button buttonHour(BUTTON_PIN_HOUR); // Button for time adjust add hour
RBD::Button buttonMinute(BUTTON_PIN_MINUTE); // Button for time adjust add minute

// TIME
unsigned long _hour = 0;
unsigned long _minute = 0;
unsigned long _second = 0;
unsigned long _milli = 0;
militaryTime _mTime = militaryTime();
desamberTime _dTime = desamberTime();

void setup()
{
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();
}

void loop()
{
  // SHARED VARIABLES
  _hour = (unsigned long) hour();
  _minute = (unsigned long) minute();
  _second = (unsigned long) second();

  // This keeps the _milli value under 1000 for dTime calculations.
  String milliString = String(millis());
  _milli = String(millis()).substring(milliString.length()-3, milliString.length()).toInt();

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
  writeToScreen(_mTime.getTime(_hour, _minute, _second, _milli), ROW_OFFSET_ZERO, 0);

  // Print Desamber time to LCD
  writeToScreen(_dTime.getTime(_hour, _minute, _second, _milli), ROW_OFFSET_ONE, 1);

  // '...the shortest pulse equals to 8.64 milliseconds...'
  delay(86);
}

void writeToScreen(String value, int posX, int posY)
{
  lcd.setCursor(posX, posY);
  lcd.print(value);
}
