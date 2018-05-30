/*! \file Ardusamber.h
 *
 * This is the main header file for the %Ardusamber library.
 *
 * This is library is for using Devine Lu Linvega's time format 'Desamber' with Arduino.
 * More information about Desamber here: https://wiki.xxiivv.com/#clock
 * */

#include "Arduino.h"

class Ardusamber
{
  public:
    String getFormattedTime();
    String getFormattedDate();
    String getTimeString();
    int getTimeBeat();
    int getTimeBeatTens();
    int getTimeBeatOnes();
    int getTimePulse();
    int getTimePulseTens();
    int getTimePulseOnes();
  private:
  	String timeString;
  	String beatString;
  	int beat;
  	int beatTens;
  	int beatOnes;
  	String pulseString;
  	int pulse;
  	int pulseTens;
  	int pulseOnes;
  	String addMissingDigits(String value, int digitsRequired);
  	int calculateDayOfYear(int day, int month, int year);
};
