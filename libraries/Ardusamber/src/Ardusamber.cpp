/*
  This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
  More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include "Arduino.h"
#include "Ardusamber.h"
#include "TimeLib.h"

void Ardusamber::update()
{
  // Calculate current millisOffset.
  _secondCur = second();
  if (_secondCur != _secondPrev)
  {
    _secondPrev = _secondCur;
    _millisOffset = millis();
  }

  // Calculate Desamber beat and pulse.
  _msSinceMidnight = (hour() * 3600000UL) + (minute() * 60000UL) + (second() * 1000UL) + millis() - _millisOffset;
  _dtCalc = _msSinceMidnight / 8640.0 / 10000.0;
  dtostrf(_dtCalc, 8, 6, _dtFormatting); // format _dtCalc to 6 digits past decimal point.
  _beat = String(_dtFormatting).substring(2,5); // skip first two characters of _dtFormatting (which are "0.")
  _pulse = String(_dtFormatting).substring(5,8);
}

String Ardusamber::getTime()
{
  return _beat + _pulse;
}

String Ardusamber::getFormattedTime()
{
  return _beat + ":" + _pulse;
}

String Ardusamber::getFormattedDate()
{
  _thisDateRef = year() + month() + day();
  if (_thisDateRef == _prevFormattedDateRef)
  {
    // FormattedDate hasn't changed.
    return _prevFormattedDate;
  }
  else
  {
    // FormattedDate needs to be updated.
    _prevFormattedDateRef = _thisDateRef;
    char months[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ+";
    int doty = calculateDayOfYear(day(), month(), year());
    int month = floor(((doty - 1) / 364.0) * 26.0);
    int day = doty - (14 * month);

    _prevFormattedDate = "";
    _prevFormattedDate += String(year()).substring(2, 4);
    _prevFormattedDate += String(months[month]);
    char dayBuffer[3];
    sprintf(dayBuffer, "%02d", day);
    _prevFormattedDate += dayBuffer;

    return _prevFormattedDate;
  }
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