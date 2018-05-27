#include <Arduino.h>
#include <Bun.h>

Bun::Bun(int pin)
{
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}

bool Bun::isPressed()
{
  return !digitalRead(_pin);
}

bool Bun::isReleased()
{
  return !isPressed();
}

bool Bun::onPressed()
{
  if(isPressed())
  {
    if(!_onPressedDone)
    {
      return _onPressedDone = true;
    }
    return false;
  }
  // else
  _onPressedDone = false;
  return false;
}

bool Bun::onReleased()
{
  if(isReleased())
  {
    if(!_onReleasedDone)
    {
      return _onReleasedDone = true;
    }
    return false;
  }
  // else isPressed()
  _onReleasedDone = false;
  return false;
}