#include <Arduino.h>

class Bun
{
  public:
    Bun(int pin);
    bool isPressed();
    bool isReleased();
    bool onPressed();
    bool onReleased();
  private:
    int _pin;
    bool _onPressedDone  = false;
    bool _onReleasedDone = false;
};