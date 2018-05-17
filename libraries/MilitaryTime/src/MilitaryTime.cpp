/*
  This is simple library is for handling formatted 24-hour time.
*/

#include "Arduino.h"
#include "MilitaryTime.h"
#include "TimeLib.h"

String MilitaryTime::getFormattedTime()
{
  String formattedTime = addMissingDigits(String(hour()), 2);
  formattedTime += ':';
  formattedTime += addMissingDigits(String(minute()), 2);
  formattedTime += ':';
  formattedTime += addMissingDigits(String(second()), 2);
  return formattedTime;
}

String MilitaryTime::getFormattedDate()
{
  return String(year()).substring(2, 4)
    + "-" 
    + addMissingDigits(String(month()), 2) 
    + "-" 
    + addMissingDigits(String(day()), 2);
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
