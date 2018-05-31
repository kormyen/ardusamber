/*
  This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
  More information about Desamber here: https://wiki.xxiivv.com/#clock
*/

#include "Arduino.h"
#include "Ardusamber.h"
#include "TimeLib.h"
#include "Math.h"
#include "stdlib.h"

String Ardusamber::getFormattedTime()
{
  secondCur = second();
  if (secondCur != secondPrev)
  {
    secondPrev = secondCur;
    millisOffset = millis();
  }

  // Calculate Desamber time. 10,800,000 + 3,180,000 + 33,000 + 23 = 14,013,023
  unsigned long msSinceMidnight = (hour() * 3600000UL) + (minute() * 60000UL) + (second() * 1000UL) + millis() - millisOffset;
  double val = msSinceMidnight / 8640.0 / 10000.0; /// 86.4; // 4 byte float (double) to hold 6 decimal places
  char charVal[9];
  String valString = dtostrf(val, 9, 6, charVal); // 9 digits total (incl decimal point), 6 digits after decimal point. 

  beatString = "";
  // BEAT
  for (int i = 3; i < 6; ++i)
  {
    beatString += charVal[i];
  }
  beat = beatString.toInt();
  beatTens = beatString.substring(1,3).toInt();
  beatOnes = beatString.substring(2,3).toInt();

  // PULSE
  pulseString = "";
  for (int i = 6; i < 9; ++i)
  {
    if (charVal[i] != 0)
    {
      pulseString += charVal[i];
    }
    else
    {
      pulseString += 0;
    }
  }
  pulse = pulseString.toInt();
  pulseTens = pulseString.substring(1,3).toInt();
  pulseOnes = pulseString.substring(2,3).toInt();

  timeString = beatString + pulseString;

  Serial.print(timeString);
  Serial.print(". msSinceMidnight = ");
  Serial.print(msSinceMidnight);
  Serial.print(". hour = ");
  Serial.print(hour());
  Serial.print(". minute = ");
  Serial.print(minute());
  Serial.print(". second = ");
  Serial.print(second());
  Serial.print(". millis = ");
  Serial.println(millis() - millisOffset);

  return beatString + ":" + pulseString;
}

String Ardusamber::getTimeString()
{
  return timeString;
}

int Ardusamber::getTimeBeat()
{
  return beat;
}

int Ardusamber::getTimeBeatTens()
{
  return beatTens;
}

int Ardusamber::getTimeBeatOnes()
{
  return beatOnes;
}

int Ardusamber::getTimePulse()
{
  return pulse;
}

int Ardusamber::getTimePulseTens()
{
  return pulseTens;
}

int Ardusamber::getTimePulseOnes()
{
  return pulseOnes;
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