#include "Ardusamber.h"
#include "Bun.h"
#include "TimeLib.h"
#include "TFT_ILI9163C.h"

#define OFFSET_H 14
#define OFFSET_V 6

#define CONTAINER_SIZE 100
#define SEPERATION 8
#define TIME_H 25

#define LINEOFFSET_START 1
#define LINEOFFSET_END -1

//#define DEBUG 0

typedef void (*DrawLineCallback)(int, int, uint16_t);

Ardusamber _dTime;
TFT_ILI9163C _tft = TFT_ILI9163C(10, 8, 9);

Bun _buttonBeatTwo(2);
Bun _buttonBeatThree(3);
Bun _buttonPulseOne(4);

int _beatOnePos;
int _beatOnePosPrev;
int _beatTwoPos;
int _beatTwoPosPrev;
int _beatThreePos;
int _beatThreePosPrev;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  setTime(5, 20, 00, 1, 6, 2018);

  _tft.begin();
  _tft.fillScreen(BLACK);
  _tft.setTextColor(WHITE,BLACK);
  _tft.setTextSize(1);
  
  drawContainer();

  // Pre setup so prev values can be set.
  _dTime.update();
  calcLinePositions();
  setPrevValues();
}

void loop()
{
  if(_buttonBeatTwo.isPressed()) 
  {
    adjustTime(864);
  }
  if(_buttonBeatThree.isPressed()) 
  {
    adjustTime(86.4);
  }
  if(_buttonPulseOne.isPressed()) 
  {
    adjustTime(8.64);
  }

  // 24h*60m*60s = 86400 total seconds per day
  // beat1  = 8640 s
  // beat2  =  864 s
  // beat3  =   86.4 s
  // pulse1 =    8.64 s
  // pulse2 =    0.864 s
  // pulse3 =    0.0864 s

  _dTime.update();
  
  drawClock();
  drawText();
  
  delay(86);
}

void drawContainer()
{
  _tft.drawFastVLine( OFFSET_H, OFFSET_V, CONTAINER_SIZE, WHITE); // L
  _tft.drawFastHLine( OFFSET_H, OFFSET_V, CONTAINER_SIZE, WHITE); // T
  _tft.drawFastVLine( OFFSET_H + CONTAINER_SIZE, OFFSET_V, CONTAINER_SIZE + 1, WHITE); // R
  _tft.drawFastHLine( OFFSET_H, OFFSET_V + CONTAINER_SIZE, CONTAINER_SIZE, WHITE); // B
}

void calcLinePositions()
{
  _beatOnePos = (_dTime.getTime().toInt() / 1000000.00) * (CONTAINER_SIZE - 1);
  _beatTwoPos = (_dTime.getTime().substring(1,6).toInt() / 100000.00) * (CONTAINER_SIZE - 1);
  _beatThreePos = (_dTime.getTime().substring(2,6).toInt() / 10000.00) * ((CONTAINER_SIZE - 2) - _beatOnePos) + _beatOnePos;
}

void setPrevValues()
{
  _beatOnePosPrev = _beatOnePos;
  _beatTwoPosPrev = _beatTwoPos;
  _beatThreePosPrev = _beatThreePos;
}

void drawClock()
{
  calcLinePositions();

  CalcLine(_beatThreePosPrev, _beatThreePos, CONTAINER_SIZE, _beatTwoPosPrev, _beatTwoPos, drawLineThree); // 3
  CalcLine(_beatTwoPosPrev, _beatTwoPos, CONTAINER_SIZE, _beatOnePosPrev, _beatOnePos, drawLineTwo); // 2
  CalcLine(_beatOnePosPrev, _beatOnePos, CONTAINER_SIZE, LINEOFFSET_START, LINEOFFSET_START, drawLineOne); // 1
  
  setPrevValues();
}

void CalcLine(int prev, int cur, int lineEnd, int refPrev, int refCur, DrawLineCallback doDraw)
{
  if (cur != prev)
  {
    if (prev != 0 && prev != lineEnd)
    {
      // Clear line if it is not on another line
      doDraw(prev, refPrev, BLACK);
    }

    doDraw(cur, refCur, WHITE);
  }
}

void drawLineOne(int vOffset, int hOffset, uint16_t color)
{
  #ifdef DEBUG
  if (color == 0xFFFF)
  {
    color = 0x001F; // blue
  }
  else
  {
    color = 0x000F; // navy
  }
  #endif
  _tft.drawFastHLine(OFFSET_H + hOffset, OFFSET_V + vOffset + 1, CONTAINER_SIZE + LINEOFFSET_END, color);
}

void drawLineTwo(int hOffset, int vOffset, uint16_t color)
{
  #ifdef DEBUG
  if (color == 0xFFFF)
  {
    color = 0x07E0; // green
  }
  else
  {
    color = 0x03E0; // dark green
  }
  #endif
  _tft.drawFastVLine(OFFSET_H + hOffset + 1, OFFSET_V + vOffset + 2, CONTAINER_SIZE + LINEOFFSET_END - vOffset - 1, color);
}

void drawLineThree(int vOffset, int hOffset, uint16_t color)
{
  if (vOffset < CONTAINER_SIZE - 2) // Don't render if height exceeded
  {
    #ifdef DEBUG
    if (color == 0xFFFF)
    {
      color = 0xF800; // red
    }
    else
    {
      color = 0x7800; // magenta
    }
    #endif
    _tft.drawFastHLine(OFFSET_H + hOffset + 2, OFFSET_V + vOffset + 2, CONTAINER_SIZE - hOffset - 2, color);
  }
}

void drawText()
{
  _tft.setCursor(TIME_H, OFFSET_V + CONTAINER_SIZE + SEPERATION);
  _tft.println(_dTime.getFormattedDate() + " " + _dTime.getFormattedTime());
}
