/*
  This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
  More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include "Arduino.h"
#include "Ardusamber.h"
#include "TimeLib.h"

String Ardusamber::getFormattedTime()
{
  // This keeps the _milli value under 1000 for dTime calculations.
  String milliString = String(millis());
  unsigned long milli = String(millis()).substring(milliString.length()-3, milliString.length()).toInt();

  // Calculate Desamber time
  unsigned long dTime = ((hour() * 3600000) + (minute() * 60000) + (second() * 1000) + milli) / 86.4;

  // Format to string with filler zero characters up to six total characters
  String dTimeString = addMissingDigits(String(dTime), 6);

  String formattedTime = dTimeString.substring(0, 3);
  formattedTime += ":";
  formattedTime += dTimeString.substring(3, 6);
  return formattedTime;
}

String Ardusamber::addMissingDigits(String value, int digitsRequired)
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
