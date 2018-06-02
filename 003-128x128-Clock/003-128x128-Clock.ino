#include "Ardusamber.h"
#include "Bun.h"
#include "TimeLib.h"
#include "TFT_ILI9163C.h"

#define CLOCK_X 14
#define CLOCK_Y 6
#define CLOCK_SIZE 100
#define CLOCK_LINE_THICKNESS 1

#define TEXT_X 25
#define TEXT_MARGIN_Y 8

//#define LINEOFFSET_START 1
//#define LINEOFFSET_END -1

#define DEBUG 0

// DEBUG COLORS
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define DARKGREY        0x7BEF      /* 128, 128, 128 */
#define BLACK           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define PURPLE          0x780F      /* 128,   0, 128 */

typedef void (*DrawLineCallback)(int, int, int, uint16_t);

Ardusamber _dTime;
TFT_ILI9163C _tft = TFT_ILI9163C(10, 8, 9);

Bun _buttonBeatTwo(2);
Bun _buttonBeatThree(3);
Bun _buttonPulseOne(4);

float _beatOnePerc;
float _beatOnePercPrev;
float _beatTwoPerc;
float _beatTwoPercPrev;
float _beatThreePerc;
float _beatThreePercPrev;

uint16_t _containerColor = WHITE;

void setup()
{
  Serial.begin(9600);
  #ifdef DEBUG
  //_containerColor = 0x7BEF; // dark grey
  #endif
  
  setTime(5, 20, 00, 1, 6, 2018);

  _tft.begin();
  _tft.fillScreen(BLACK);
  _tft.setTextColor(WHITE,BLACK);
  _tft.setTextSize(1);
  
  drawContainer();
  
  // Pre-setup so prev values can be set.
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
  _tft.drawFastVLine( CLOCK_X, CLOCK_Y, CLOCK_SIZE, _containerColor); // L
  _tft.drawFastHLine( CLOCK_X, CLOCK_Y, CLOCK_SIZE, _containerColor); // T
  _tft.drawFastVLine( CLOCK_X + CLOCK_SIZE, CLOCK_Y, CLOCK_SIZE + 1, _containerColor); // R
  _tft.drawFastHLine( CLOCK_X, CLOCK_Y + CLOCK_SIZE, CLOCK_SIZE, _containerColor); // B
}

void calcLinePositions()
{
  _beatOnePerc = (_dTime.getTime().toInt() / 1000000.00);
  _beatTwoPerc = (_dTime.getTime().substring(1,6).toInt() / 100000.00);
  _beatThreePerc = (_dTime.getTime().substring(2,6).toInt() / 10000.00); 
}

void setPrevValues()
{
  _beatOnePercPrev = _beatOnePerc;
  _beatTwoPercPrev = _beatTwoPerc;
  _beatThreePercPrev = _beatThreePerc;
}


// The problem before was that I was not taking into account that the prev and cur lines are different lengths
void drawClock()
{
  calcLinePositions();



  // 1
  int one_xPrev = CLOCK_LINE_THICKNESS;
  int one_yPrev = CLOCK_LINE_THICKNESS + (_beatOnePercPrev * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int one_lPrev = CLOCK_SIZE - CLOCK_LINE_THICKNESS;

  int one_xCur = CLOCK_LINE_THICKNESS;
  int one_yCur = CLOCK_LINE_THICKNESS + (_beatOnePerc * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int one_lCur = CLOCK_SIZE - CLOCK_LINE_THICKNESS;

  // 2
  int two_xPrev = CLOCK_LINE_THICKNESS + (_beatTwoPercPrev * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int two_yPrev = CLOCK_LINE_THICKNESS * 2 + (_beatOnePercPrev * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int two_lPrev = CLOCK_SIZE - CLOCK_LINE_THICKNESS - (_beatOnePercPrev * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));

  int two_xCur = CLOCK_LINE_THICKNESS + (_beatTwoPerc * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int two_yCur = CLOCK_LINE_THICKNESS * 2 + (_beatOnePerc * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));
  int two_lCur = CLOCK_SIZE - CLOCK_LINE_THICKNESS - (_beatOnePerc * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));

  // 3
  int three_xPrev = CLOCK_LINE_THICKNESS + two_xPrev;
  int three_yPrev = CLOCK_LINE_THICKNESS + one_yPrev + (_beatThreePercPrev * ((CLOCK_SIZE - CLOCK_LINE_THICKNESS) - one_yPrev));
  int three_lPrev = CLOCK_SIZE - CLOCK_LINE_THICKNESS - (_beatTwoPercPrev * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));

  int three_xCur = CLOCK_LINE_THICKNESS + two_xCur;
  int three_yCur = CLOCK_LINE_THICKNESS + one_yCur + (_beatThreePerc * ((CLOCK_SIZE - CLOCK_LINE_THICKNESS) - one_yCur));
  int three_lCur = CLOCK_SIZE - CLOCK_LINE_THICKNESS - (_beatTwoPerc * (CLOCK_SIZE - CLOCK_LINE_THICKNESS));

  



  if (three_yCur < CLOCK_SIZE) // Don't render if height exceeded (happens around 992:000+)
  {
    if (three_yPrev != three_yCur)
    {
      _tft.drawFastHLine(CLOCK_X + three_xPrev, CLOCK_Y + three_yPrev, three_lPrev, MAROON); // BLACK
      _tft.drawFastHLine(CLOCK_X + three_xCur, CLOCK_Y + three_yCur, three_lCur, RED); // WHITE
    }
  }

  if (two_xPrev != two_xCur)
  {
    _tft.drawFastVLine(CLOCK_X + two_xPrev, CLOCK_Y + two_yPrev, two_lPrev, DARKGREEN); // BLACK
    _tft.drawFastVLine(CLOCK_X + two_xCur, CLOCK_Y + two_yCur, two_lCur, GREEN); // WHITE
  }

  if (one_yPrev != one_yCur)
  {
    _tft.drawFastHLine(CLOCK_X + one_xPrev, CLOCK_Y + one_yPrev, one_lPrev, NAVY); // BLACK
    _tft.drawFastHLine(CLOCK_X + one_xCur, CLOCK_Y + one_yCur, one_lCur, BLUE); // WHITE
  }

  //drawContainer();

  setPrevValues();
}

void CalcLineHorizontal(int xPrev, int yPrev, int xCur, int yCur, int lineLength, uint16_t cPrev, uint16_t cCur)
{
  if (yPrev != yCur)
  {
    _tft.drawFastHLine(CLOCK_X + xPrev, CLOCK_Y + yPrev, lineLength, cPrev);
    _tft.drawFastHLine(CLOCK_X + xCur, CLOCK_Y + yCur, lineLength, cCur);
  }
}

void drawText()
{
  _tft.setCursor(TEXT_X, CLOCK_Y + CLOCK_SIZE + TEXT_MARGIN_Y);
  _tft.println(_dTime.getFormattedDate() + " " + _dTime.getFormattedTime());
}
