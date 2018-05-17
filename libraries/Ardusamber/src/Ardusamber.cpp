/*
  This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
  More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include "Arduino.h"
#include "Ardusamber.h"
#include "TimeLib.h"
#include "Math.h"

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

String Ardusamber::getFormattedDate()
{
  char months[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ+";
  int doty = calculateDayOfYear(day(), month(), year());

  int month = floor(((doty - 1) / 364.0) * 26.0);
  //month += floor(doty / 14) + 1;
  
  int day = doty - (14 * month);
  //String day = addMissingDigits(String(doty % 26), 2);
  // addMissingDigits(day, 2)

  String formattedTime;
  //formattedTime += doty;
  //formattedTime += "   ";
  formattedTime += String(year()).substring(2, 4);
  formattedTime += String(months[month]);
  formattedTime += addMissingDigits(String(day), 2);

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

// Source: https://gist.github.com/jrleeman/3b7c10712112e49d8607
int Ardusamber::calculateDayOfYear(int day, int month, int year)
{
  // Given a day, month, and year (4 digit), returns 
  // the day of year. Errors return 999.
  
  int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  
  // Verify we got a 4-digit year
  if (year < 1000) {
    return 999;
  }
  
  // Check if it is a leap year, this is confusing business
  // See: https://support.microsoft.com/en-us/kb/214019
  if (year%4  == 0) {
    if (year%100 != 0) {
      daysInMonth[1] = 29;
    }
    else {
      if (year%400 == 0) {
        daysInMonth[1] = 29;
      }
    }
   }

  // Make sure we are on a valid day of the month
  if (day < 1) 
  {
    return 999;
  } else if (day > daysInMonth[month-1]) {
    return 999;
  }
  
  int doy = 0;
  for (int i = 0; i < month - 1; i++) {
    doy += daysInMonth[i];
  }
  
  doy += day;
  return doy;
}