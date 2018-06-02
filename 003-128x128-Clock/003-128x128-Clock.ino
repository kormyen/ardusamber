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

//#define DEBUG 0 // Uncomment this line to enable debug mode

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

#ifndef DEBUG
#define COLOR_ONE_CUR WHITE
#define COLOR_ONE_PREV BLACK
#define COLOR_TWO_CUR WHITE
#define COLOR_TWO_PREV BLACK
#define COLOR_THREE_CUR WHITE
#define COLOR_THREE_PREV BLACK
#else
#define COLOR_ONE_CUR BLUE
#define COLOR_ONE_PREV NAVY
#define COLOR_TWO_CUR GREEN
#define COLOR_TWO_PREV DARKGREEN
#define COLOR_THREE_CUR RED
#define COLOR_THREE_PREV MAROON
#endif

typedef void (*DrawLineCallback)(int, int, int, uint16_t);

Ardusamber _dTime;
TFT_ILI9163C _tft = TFT_ILI9163C(10, 8, 9);
Bun _buttonBeatTwo(2);
Bun _buttonBeatThree(3);
Bun _buttonPulseOne(4);

const int LINE_LENGTH = CLOCK_SIZE - CLOCK_LINE_THICKNESS;
float _onePerc;
float _onePercPrev;
float _twoPerc;
float _twoPercPrev;
float _threePerc;
float _threePercPrev;
int one_x = CLOCK_LINE_THICKNESS;
int one_yPrev = CLOCK_LINE_THICKNESS;
int one_yCur = CLOCK_LINE_THICKNESS;
int two_xPrev;
int two_yPrev;
int two_lPrev;
int two_xCur;
int two_yCur;
int two_lCur;
int three_xPrev;
int three_yPrev;
int three_lPrev;
int three_xCur;
int three_yCur;
int three_lCur;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  setTime(5, 30, 00, 3, 6, 2018);

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

    // Hack fix to clean up missed lines - this happens on large time changes
    _tft.fillRect(CLOCK_X + CLOCK_LINE_THICKNESS, CLOCK_Y + CLOCK_LINE_THICKNESS, CLOCK_SIZE - CLOCK_LINE_THICKNESS, CLOCK_SIZE - CLOCK_LINE_THICKNESS, BLACK);
  }
  if(_buttonBeatThree.isPressed()) 
  {
    adjustTime(86.4);
  }
  if(_buttonPulseOne.isPressed()) 
  {
    adjustTime(8.64);
  }

  _dTime.update();
  drawClock();

  // TEXT
  _tft.setCursor(TEXT_X, CLOCK_Y + CLOCK_SIZE + TEXT_MARGIN_Y);
  _tft.println(_dTime.getFormattedDate() + " " + _dTime.getFormattedTime());
  
  delay(8.6);
}

void drawClock()
{
  // PERCENT
  _onePerc = (_dTime.getTime().toInt() / 1000000.00);
  _twoPerc = (_dTime.getTime().substring(1,6).toInt() / 100000.00);
  _threePerc = (_dTime.getTime().substring(2,6).toInt() / 10000.00); 

  // LINE
  one_yCur = CLOCK_LINE_THICKNESS + (_onePerc * LINE_LENGTH);
  two_xCur = CLOCK_LINE_THICKNESS + (_twoPerc * LINE_LENGTH);
  two_yCur = CLOCK_LINE_THICKNESS * 2 + (_onePerc * LINE_LENGTH);
  two_lCur = LINE_LENGTH - (_onePerc * LINE_LENGTH);
  three_xCur = CLOCK_LINE_THICKNESS + two_xCur;
  three_yCur = CLOCK_LINE_THICKNESS + one_yCur + (_threePerc * (LINE_LENGTH - one_yCur));
  //three_lCur = LINE_LENGTH - (_twoPerc * LINE_LENGTH);
  three_lCur = LINE_LENGTH + CLOCK_LINE_THICKNESS - three_xCur;

  Serial.print("two_xCur = ");
  Serial.print(two_xCur);
  Serial.print(". three_xCur = ");
  Serial.print(three_xCur);
  Serial.print(". three_lCur = ");
  Serial.println(three_lCur);
    
  // ERASE
  if (three_yCur < CLOCK_SIZE) // Don't render if height exceeded (happens around 992:000+)
  {
    if (three_yPrev != three_yCur)
    {
      _tft.drawFastHLine(CLOCK_X + three_xPrev, CLOCK_Y + three_yPrev, three_lPrev, COLOR_THREE_PREV); // BLACK
    }
  }
  if (two_xPrev != two_xCur)
  {
    _tft.drawFastVLine(CLOCK_X + two_xPrev, CLOCK_Y + two_yPrev, two_lPrev, COLOR_TWO_PREV); // BLACK
  }
  if (one_yPrev != one_yCur)
  {
    _tft.drawFastHLine(CLOCK_X + one_x, CLOCK_Y + one_yPrev, LINE_LENGTH, COLOR_ONE_PREV); // BLACK

  }
  
  // DRAW
  if (one_yPrev != one_yCur)
  {
    _tft.drawFastHLine(CLOCK_X + one_x, CLOCK_Y + one_yCur, LINE_LENGTH, COLOR_ONE_CUR); // WHITE
  }
  if (two_xPrev != two_xCur)
  {
    _tft.drawFastVLine(CLOCK_X + two_xCur, CLOCK_Y + two_yCur, two_lCur, COLOR_TWO_CUR); // WHITE
  }
  if (three_yCur < CLOCK_SIZE) // Don't render if height exceeded (happens around 992:000+)
  {
    if (three_yPrev != three_yCur)
    {
      _tft.drawFastHLine(CLOCK_X + three_xCur, CLOCK_Y + three_yCur, three_lCur, COLOR_THREE_CUR); // WHITE
    }
  }

  // PREV
  _onePercPrev = _onePerc;
  _twoPercPrev = _twoPerc;
  _threePercPrev = _threePerc;
  one_yPrev = one_yCur;
  two_xPrev = two_xCur;
  two_yPrev = two_yCur;
  two_lPrev = two_lCur;
  three_xPrev = three_xCur;
  three_yPrev = three_yCur;
  three_lPrev = three_lCur;
}
