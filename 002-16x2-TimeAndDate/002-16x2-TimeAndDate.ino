/*
 * This Arduino sketch displays four screens of different time and date formats on a 16 character by 2 line display.
 * The forth button changes mode.
 * 
 * The first mode displays Desamber time and date.
 * The second mode displays 24-hour time and YY-MM-DD.
 * The third mode displays Desamber time and 24-hour time. In this mode buttons one, two and three change the time.
 * The forth mode displays the Desamber date and YY-MM-DD. In this mode buttons one, two and three change the date.
 * Desamber is a time format created by Devine Lu Linvega. More information about Desamber here: https://wiki.xxiivv.com/#clock
 */

#include "Ardusamber.h"
#include "MilitaryTime.h"
#include "Bun.h"
#include "TimeLib.h"
#include "LiquidCrystal_I2C.h"

enum Mode 
{
  DESC,
  DESAMBER,
  GREGORIAN,
  TIME,
  DATE
};
Mode _mode = DESC;

Ardusamber _dTime;
MilitaryTime _mTime;
LiquidCrystal_I2C _lcd(0x20,16,2); // Set the LCD address to 0x20 for a 16 chars and 2 line display

Bun buttonOne(7);
Bun buttonTwo(6);
Bun buttonThree(5);
Bun buttonMode(4);

void setup()
{
  setTime(17,32, 00, 17, 5, 2018);
  
  _lcd.init();
  _lcd.backlight();
  _lcd.home();
  _lcd.clear();
}

void loop()
{
  _dTime.update();
  
  if(buttonMode.isPressed()) 
  {
    if (_mode == DESC)
    {
      _lcd.clear();
      _mode = DESAMBER;
    }
    else if (_mode == DESAMBER)
    {
      _lcd.clear();
      _mode = GREGORIAN;
    }
    else if (_mode == GREGORIAN)
    {
      _lcd.clear();
      _mode = TIME;
    }
    else if (_mode == TIME)
    {
      _lcd.clear();
      _mode = DATE;
    }
    else if (_mode == DATE)
    {
      _lcd.clear();
      _mode = DESC;
    }
  }

  if (_mode == DESC)
  {
    writeToScreen("The Time is", 2, 0);
    writeToScreen(_dTime.getFormattedTime() + ".", 4, 1);
    delay(86);
  }
  else if (_mode == DESAMBER)
  {
    writeToScreen(_dTime.getFormattedTime(), 4, 0);
    writeToScreen(_dTime.getFormattedDate(), 6, 1);
    delay(86);
  }
  else if (_mode == GREGORIAN)
  {
    writeToScreen(_mTime.getFormattedTime(), 4, 0);
    writeToScreen(_mTime.getFormattedDate(), 4, 1);
    delay(100);
  }
  else if (_mode == TIME)
  {
    if(buttonOne.isPressed()) 
    {
      adjustTime(3600);
    }
    if(buttonTwo.isPressed()) 
    {
      adjustTime(60);
    }
    if(buttonThree.isPressed()) 
    {
      adjustTime(1);
    }

    writeToScreen(_mTime.getFormattedTime(), 4, 0);
    writeToScreen(_dTime.getFormattedTime(), 5, 1);
    delay(86);
  }
  else if (_mode == DATE)
  {
    if(buttonOne.isPressed()) 
    {
      // Add year
      setTime(hour(),minute(),second(),day(),month(),year()+1);
    }
    if(buttonTwo.isPressed()) 
    {
      // Add month
      setTime(hour(),minute(),second(),day(),month()+1,year());
    }
    if(buttonThree.isPressed()) 
    {
      // Add day
      setTime(hour(),minute(),second(),day()+1,month(),year());
    }

    writeToScreen(_mTime.getFormattedDate(), 4, 0);
    writeToScreen(_dTime.getFormattedDate(), 7, 1);
    delay(86);
  }
}

void writeToScreen(String value, int posX, int posY)
{
  _lcd.setCursor(posX, posY);
  _lcd.print(value);
}
