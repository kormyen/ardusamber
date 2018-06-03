#include "Ardusamber.h"
#include "Bun.h"
#include "TimeLib.h"
#include "TFT_ILI9163C.h"

//#define DEBUG 0 // uncomment this line to enable debug mode (rgb lines)

#define BLACK             0x0000
#define WHITE             0xFFFF
#define BLUE              0x001F
#define NAVY              0x000F
#define GREEN             0x07E0
#define DARKGREEN         0x03E0
#define RED               0xF800
#define MAROON            0x7800

#ifndef DEBUG
#define COLOR_ONE_CUR     WHITE
#define COLOR_ONE_PREV    BLACK
#define COLOR_TWO_CUR     WHITE
#define COLOR_TWO_PREV    BLACK
#define COLOR_THREE_CUR   WHITE
#define COLOR_THREE_PREV  BLACK
#define COLOR_FOUR_CUR    WHITE
#define COLOR_FOUR_PREV   BLACK
#define COLOR_FIVE_CUR    WHITE
#define COLOR_FIVE_PREV   BLACK
#define COLOR_SIX_CUR     WHITE
#define COLOR_SIX_PREV    BLACK
#else
#define COLOR_ONE_CUR     BLUE
#define COLOR_ONE_PREV    NAVY
#define COLOR_TWO_CUR     GREEN
#define COLOR_TWO_PREV    DARKGREEN
#define COLOR_THREE_CUR   RED
#define COLOR_THREE_PREV  MAROON
#define COLOR_FOUR_CUR    BLUE
#define COLOR_FOUR_PREV   NAVY
#define COLOR_FIVE_CUR    GREEN
#define COLOR_FIVE_PREV   DARKGREEN
#define COLOR_SIX_CUR     RED
#define COLOR_SIX_PREV    MAROON
#endif

#define CLOCK_X           14
#define CLOCK_Y           6
#define CLOCK_SIZE        100
#define LINE_THICKNESS    1
#define TEXT_X            25
#define TEXT_MARGIN_Y     8

Ardusamber _dTime;
TFT_ILI9163C _tft = TFT_ILI9163C(10, 8, 9);
Bun _buttonBeatTwo(2);
Bun _buttonBeatThree(3);
Bun _buttonPulseOne(4);

bool _forceRedraw;
const int LINE_LENGTH = CLOCK_SIZE - LINE_THICKNESS;

float _onePerc;
float _twoPerc;
float _threePerc;
float _fourPerc;
float _fivePerc;
float _sixPerc;

// 0 xCur, 1 yCur, 2 lCur, 3 xPrev, 4 yPrev, 5 lPrev
int _one[6];
int _two[6];
int _three[6];
int _four[6];
int _five[6];
int _six[6];

void setup()
{
  setTime(3, 00, 00, 4, 6, 2018);

  _one[0] = LINE_THICKNESS; // xCur
  _one[1] = LINE_THICKNESS; // yCur
  _one[4] = LINE_THICKNESS; // yPrev

  _tft.begin();
  _tft.fillScreen(BLACK);
  _tft.setTextColor(WHITE,BLACK);
  _tft.setTextSize(1);

  // CONTAINER
  _tft.drawFastVLine(CLOCK_X, CLOCK_Y, CLOCK_SIZE, WHITE); // L
  _tft.drawFastHLine(CLOCK_X, CLOCK_Y, CLOCK_SIZE, WHITE); // T
  _tft.drawFastVLine(CLOCK_X + CLOCK_SIZE, CLOCK_Y, CLOCK_SIZE + 1, WHITE); // R
  _tft.drawFastHLine(CLOCK_X, CLOCK_Y + CLOCK_SIZE, CLOCK_SIZE, WHITE); // B
}

void loop()
{
  // 24h*60m*60s = 86400 total seconds per day
  // beat1  = 8640 s
  // beat2  =  864 s
  // beat3  =   86.4 s
  // pulse1 =    8.64 s
  // pulse2 =    0.864 s
  // pulse3 =    0.0864 s
  
  if(_buttonBeatTwo.isPressed()) 
  {
    adjustTime(864);
    refresh();
  }
  if(_buttonBeatThree.isPressed()) 
  {
    adjustTime(86.4);
    refresh();
  }
  if(_buttonPulseOne.isPressed()) 
  {
    adjustTime(8.64);
    refresh();
  }

  _dTime.update();

  drawClock(_dTime.getTime());

  // TEXT
  _tft.setCursor(TEXT_X, CLOCK_Y + CLOCK_SIZE + TEXT_MARGIN_Y);
  _tft.println(_dTime.getFormattedDate() + " " + _dTime.getFormattedTime());
  
  delay(1);
}

void drawClock(String dtime)
{
  // PERCENT
  _onePerc = (dtime.toInt() / 1000000.00);                // H
  _twoPerc = (dtime.substring(1,6).toInt() / 100000.00);  // V
  _threePerc = (dtime.substring(2,6).toInt() / 10000.00); // H
  _fourPerc = (dtime.substring(3,6).toInt() / 1000.00);   // V
  _fivePerc = (dtime.substring(4,6).toInt() / 100.00);    // H
  _sixPerc = (dtime.substring(5,6).toInt() / 10.00);      // V

  // CURRENT
  _one[1] = LINE_THICKNESS + (_onePerc * LINE_LENGTH);
  _two[0] = LINE_THICKNESS + (_twoPerc * LINE_LENGTH);
  _two[1] = LINE_THICKNESS * 2 + (_onePerc * LINE_LENGTH);
  _two[2] = LINE_LENGTH - (_onePerc * LINE_LENGTH);
  _three[0] = LINE_THICKNESS + _two[0];
  _three[1] = min(LINE_THICKNESS + _one[1] + (_threePerc * (LINE_LENGTH - _one[1])), LINE_LENGTH);
  _three[2] = LINE_LENGTH + LINE_THICKNESS - _three[0];
  _four[0] = min(LINE_THICKNESS + _two[0] + (_fourPerc * (LINE_LENGTH - _two[0])), LINE_LENGTH);
  _four[1] = LINE_THICKNESS + _three[1];
  _four[2] = LINE_LENGTH - _three[1];
  _five[0] = LINE_THICKNESS + _four[0];
  _five[1] = min(LINE_THICKNESS + _three[1] + (_fivePerc * (LINE_LENGTH - _three[1])), LINE_LENGTH);
  _five[2] = LINE_LENGTH - _four[0];
  _six[0] = min(LINE_THICKNESS + _four[0] + (_sixPerc * (LINE_LENGTH - _four[0])), LINE_LENGTH);
  _six[1] = LINE_THICKNESS + _five[1];
  _six[2] = LINE_LENGTH - _five[1];
    
  // ERASE
  if (_six[3] != _six[0]) // six's xPrev != xCur
  {
    _tft.drawFastVLine(CLOCK_X + _six[3], CLOCK_Y + _six[4], _six[5], COLOR_SIX_PREV);
  }
  if (_five[4] != _five[1]) // five's yPrev != yCur
  {
    _tft.drawFastHLine(CLOCK_X + _five[3], CLOCK_Y + _five[4], _five[5], COLOR_FIVE_PREV);
  }
  if (_four[3] != _four[0]) // four's xPrev != xCur
  {
    _tft.drawFastVLine(CLOCK_X + _four[3], CLOCK_Y + _four[4], _four[5], COLOR_FOUR_PREV);
  }
  if (_three[4] != _three[1]) // three's yPrev != yCur
  {
    _tft.drawFastHLine(CLOCK_X + _three[3], CLOCK_Y + _three[4], _three[5], COLOR_THREE_PREV);
  }
  if (_two[3] != _two[0]) // two's xPrev != xCur
  {
    _tft.drawFastVLine(CLOCK_X + _two[3], CLOCK_Y + _two[4], _two[5], COLOR_TWO_PREV);
  }
  if (_one[4] != _one[1]) // one's yPrev != yCur
  {
    _tft.drawFastHLine(CLOCK_X + _one[0], CLOCK_Y + _one[4], LINE_LENGTH, COLOR_ONE_PREV);
  }
  
  // DRAW
  if (_forceRedraw || _one[4] != _one[1])
  {
    _tft.drawFastHLine(CLOCK_X + _one[0], CLOCK_Y + _one[1], LINE_LENGTH, COLOR_ONE_CUR);
  }
  if (_forceRedraw || _two[3] != _two[0])
  {
    _tft.drawFastVLine(CLOCK_X + _two[0], CLOCK_Y + _two[1], _two[2], COLOR_TWO_CUR);
  }
  if (_forceRedraw || _three[4] != _three[1])
  {
    _tft.drawFastHLine(CLOCK_X + _three[0], CLOCK_Y + _three[1], _three[2], COLOR_THREE_CUR);
  }
  if (_forceRedraw || _four[3] != _four[0])
  {
    _tft.drawFastVLine(CLOCK_X + _four[0], CLOCK_Y + _four[1], _four[2], COLOR_FOUR_CUR);
  }
  if (_forceRedraw || _five[4] != _five[1])
  {
    _tft.drawFastHLine(CLOCK_X + _five[0], CLOCK_Y + _five[1], _five[2], COLOR_FIVE_CUR);
  }
  if (_forceRedraw || _six[3] != _six[0])
  {
    _tft.drawFastVLine(CLOCK_X + _six[0], CLOCK_Y + _six[1], _six[2], COLOR_SIX_CUR);
  }
  
  // PREVIOUS
  _one[4] = _one[1]; // yPrev = yCur
  _two[3] = _two[0]; // xPrev = xCur
  _two[4] = _two[1]; // yPrev = yCur
  _two[5] = _two[2]; // lPrev = lCur
  _three[3] = _three[0]; // xPrev = xCur
  _three[4] = _three[1]; // yPrev = yCur
  _three[5] = _three[2]; // lPrev = lCur
  _four[3] = _four[0]; // xPrev = xCur
  _four[4] = _four[1]; // yPrev = yCur
  _four[5] = _four[2]; // lPrev = lCur
  _five[3] = _five[0]; // xPrev = xCur
  _five[4] = _five[1]; // yPrev = yCur
  _five[5] = _five[2]; // lPrev = lCur
  _six[3] = _six[0]; // xPrev = xCur
  _six[4] = _six[1]; // yPrev = yCur
  _six[5] = _six[2]; // lPrev = lCur
  _forceRedraw = false;
}

void refresh()
{
  // HACK FIX due to line erasing issues currently happening with the clock rendering when time is adjusted faster than real time.
  // Symptom: beat/pulse lines' top/left most sections are often (not always) left un-erased.
  _tft.fillRect(CLOCK_X + LINE_THICKNESS, CLOCK_Y + LINE_THICKNESS, LINE_LENGTH, LINE_LENGTH, BLACK); // clock blanking to clear missed lines
  _forceRedraw = true; // force redraw of all lines since they are cleared above
}
