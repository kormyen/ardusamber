/*
  This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
  More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include "Arduino.h"
#include "Ardusamber.h"
#include "TimeLib.h"
#include "Math.h"
#include "stdlib.h"

void Ardusamber::update()
{
  // Calculate current millisOffset.
  unsigned long secondCur = second();
  if (secondCur != secondPrev)
  {
    secondPrev = secondCur;
    millisOffset = millis();
  }

  // Calculate Desamber time.
  unsigned long msSinceMidnight = (hour() * 3600000UL) + (minute() * 60000UL) + (second() * 1000UL) + millis() - millisOffset;
  double dtCalc = msSinceMidnight / 8640.0 / 10000.0; /// 86.4; // 4 byte float (double) to hold 6 decimal places

  // Format Desamber time calculation.
  char dtFormatting[9];
  dtostrf(dtCalc, 8, 6, dtFormatting); // format value to 6 digits past decimal point.

  // Set Desamber values.
  beat = String(dtFormatting).substring(2,5);
  pulse = String(dtFormatting).substring(5,8);
}

String Ardusamber::getTime()
{
  return beat + pulse;
}

String Ardusamber::getFormattedTime()
{
  return beat + ":" + pulse;
}

String Ardusamber::getFormattedDate()
{
  char months[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ+";
  int doty = calculateDayOfYear(day(), month(), year());
  int month = floor(((doty - 1) / 364.0) * 26.0);
  int day = doty - (14 * month);

  String formattedTime;
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