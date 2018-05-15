/*
 Hacky version zero of an Arduino displaying Devine Lu Linvega's Desamber time format on a 16x2 LCD.
 More information on Devine Lu Linvega's Desamber time format here: https://wiki.xxiivv.com/#clock
 */

#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

int _hour = 0;
int _minute = 0;
int _second = 0;
int _milli = 0;

/*
// Ideally would use _dTime and _msSinceMidnight but can't get them to display properly. See below.
int _dTime = 0;
int _msSinceMidnight = 0;
*/

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.clear();

  //setTime(hr,min,sec,day,month,yr);
  setTime(12,35,21,15,05,2018);
}

void loop()
{
  // SHARED VARIABLES
  delay(864);
  _hour = hour();
  _minute = minute();
  _second = second();
  _milli = millis();

  
  // 24 HOUR CLOCK
  // Hours
  if (_hour < 10)
  {
    lcd.setCursor(5, 0);
    lcd.print(0);
    lcd.setCursor(6, 0);
    lcd.print(_hour);
  }
  else
  {
    lcd.setCursor(5, 0);
    lcd.print(_hour);
  }

  // Seperator
  lcd.setCursor(7, 0);
  lcd.print(':');

  // Minutes
  if (_minute < 10)
  {
    lcd.setCursor(8, 0);
    lcd.print(0);
    lcd.setCursor(9, 0);
    lcd.print(_minute);
  }
  else
  {
    lcd.setCursor(8, 0);
    lcd.print(_minute);
  }

  /*
  // Seperator
  //lcd.setCursor(10, 0);
  //lcd.print(':');

  // Seconds
  if (_second < 10)
  {
    lcd.setCursor(11, 0);
    lcd.print(0);
    lcd.setCursor(12, 0);
    lcd.print(_second);
  }
  else
  {
    lcd.setCursor(11, 0);
    lcd.print(_second);
  }
  */
  

  // DESAMBER CLOCK
  /*
  _msSinceMidnight = _hour * 60000 * 60
    + _minute * 60000
    + _milli;
    
  _dTime = (_msSinceMidnight / 864) * 10;
  
  lcd.setCursor(4, 1);
  lcd.print(_dTime); // Doesn't work... Displays "200", "-200" etc instead of correct value.
  // Can't work out how to get the int variables above to print to lcd, the code below is a mess but works.
  */
  
  // Beat 1
  lcd.setCursor(4, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 100000) % 10
    );

  // Beat 2
  lcd.setCursor(5, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 10000) % 10
    );

  // Beat 3
  lcd.setCursor(6, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 1000) % 10
    );

  // Seperator
  lcd.setCursor(7, 1);
  lcd.print(':');

  // Pulse 1
  lcd.setCursor(8, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 100) % 10
    );

  // Pulse 2
  lcd.setCursor(9, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 10) % 10
    );

  // Pulse 3
  lcd.setCursor(10, 1);
  lcd.print(
    ((((_hour * 60000 * 60
    + _minute * 60000
    + _milli)
    / 864) 
    * 10)
    / 10) % 10
    );
}
