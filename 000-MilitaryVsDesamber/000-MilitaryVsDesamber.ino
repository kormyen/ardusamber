/*
This Arduino sketch displays 24-hour time (Military time) and Desamber time.
It includes buttons to set the time. One button adds an hour, the other adds a minute.
Desamber is a time format created by Devine Lu Linvega. More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

//#define DEBUG 1

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
LiquidCrystal_I2C lcd(0x20,16,2);  // Set the LCD address to 0x20 for a 16 chars and 2 line display

// BUTTONS
RBD::Button buttonHour(BUTTON_PIN_HOUR); // Button for time adjust add hour
RBD::Button buttonMinute(BUTTON_PIN_MINUTE); // Button for time adjust add minute

// SHARED VARIABLES
unsigned long _hour = 0;
unsigned long _minute = 0;
unsigned long _second = 0;
unsigned long _milli = 0;

void setup()
{
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();

  #ifdef DEBUG
    Serial.begin(9600);
  #endif
}

void loop()
{
  // SHARED VARIABLES
  _hour = (unsigned long) hour();
  _minute = (unsigned long) minute();
  _second = (unsigned long) second();

  // This keeps our _milli value under 1000 for dTime calculations.
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
  writeToScreen(getMilitaryTime(), ROW_OFFSET_ZERO, 0);

  // Print Desamber time to LCD
  writeToScreen(getDesamberTime(), ROW_OFFSET_ONE, 1);

  // '...the shortest pulse equals to 8.64 milliseconds...'
  delay(86);
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
  unsigned long _dTime = ((_hour * 3600000) + (_minute * 60000) + (_second * 1000) + _milli) / 86.4;

  // Format to string with filler zero characters up to six total characters
  String _dTimeString = addMissingDigits(String(_dTime), 6);

  #ifdef DEBUG
    Serial.print(addMissingDigits(String(_hour), 2));
    Serial.print(":");
    Serial.print(addMissingDigits(String(_minute), 2));
    Serial.print(":");
    Serial.print(addMissingDigits(String(_second), 2));
    Serial.print(":");
    Serial.print(addMissingDigits(String(_milli), 3));
    
    Serial.print("      _dTimeString = ");
    Serial.print(_dTimeString);
  
    //Serial.print("      _dTimeMid = ");
    //Serial.print(_dTimeMid);
  
    Serial.print("      millis() = ");
    Serial.print(millis());
   
    Serial.println();
  #endif 
  
  // Add ':' seperator between beat and pulse 
  return insertString(_dTimeString, ":", 3);
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

String insertString(String text, String addition, int indexPos)
{
  String result = text.substring(0, indexPos);
  result += addition;
  result += text.substring(indexPos, text.length());
  return result;
}

