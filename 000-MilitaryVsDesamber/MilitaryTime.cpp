/*
  This is simple library is for handling formatted 24-hour time.
*/

#include "Arduino.h"
#include "MilitaryTime.h"
#include "TimeLib.h"

void MilitaryTime::loop()
{
  _formatted = addMissingDigits(String(hour()), 2);
  _formatted += ':';
  _formatted += addMissingDigits(String(minute()), 2);
  _formatted += ':';
  _formatted += addMissingDigits(String(second()), 2);
}

String MilitaryTime::getFormattedTime()
{
  return _formatted;
}

void MilitaryTime::addSeconds(int value)
{
  adjustTime(value);
}

String MilitaryTime::addMissingDigits(String value, int digitsRequired)
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
