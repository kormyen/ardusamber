/*! \file MilitaryTime.h
 *
 * This is the main header file for the %MilitaryTime library.
 *
 * This is simple library is for handling formatted 24-hour time.
 * */

#include "Arduino.h"

class MilitaryTime
{
  public:
    String getFormattedTime();
    String getFormattedDate();
  private:
  	String addMissingDigits(String value, int digitsRequired);
};
