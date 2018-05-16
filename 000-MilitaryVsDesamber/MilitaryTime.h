/*! \file Ardusamber.h
 *
 * This is the main header file for the %Ardusamber library.
 *
 * This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
 * More information about Desamber here: https://wiki.xxiivv.com/#clock
 * */

#include "Arduino.h"

class MilitaryTime
{
  public:
    void loop();
    String getFormattedTime();
    void addSeconds(int value);
  private:
    String _formatted;
  	String addMissingDigits(String value, int digitsRequired);
};
