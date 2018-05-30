#include "Ardusamber.h"

#include "TimeLib.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

Ardusamber _dTime = Ardusamber();

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

#define OFFSET_H 14
#define OFFSET_V 4
#define CONTAINER_SIZE 100

#define SEPERATION 8
#define TIME_H 22

TFT_ILI9163C tft = TFT_ILI9163C(10, 8, 9);

void setup(void)
{
  Serial.begin(9600);

  tft.begin();
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE,BLACK);
  tft.setTextSize(1);

  setTime(1, 48, 30, 30, 5, 2018);
  DrawContainer();
}

void loop()
{
  DrawClock();
  DrawText();
  delay(86);
}

void DrawContainer()
{
  tft.drawFastVLine( OFFSET_H, OFFSET_V, CONTAINER_SIZE, WHITE); // L
  tft.drawFastHLine( OFFSET_H, OFFSET_V, CONTAINER_SIZE, WHITE); // T
  
  tft.drawFastVLine( OFFSET_H + CONTAINER_SIZE, OFFSET_V, CONTAINER_SIZE + 1, WHITE); // R
  tft.drawFastHLine( OFFSET_H, OFFSET_V + CONTAINER_SIZE, CONTAINER_SIZE, WHITE); // B
}

int beatOnePosPrev = -100;
int beatTwoPosPrev = -100;
int beatThreePosPrev = -100;

void DrawClock()
{
  // Get values
  int beatOnePos = _dTime.getTimeString().toInt() / 1000000.00 * CONTAINER_SIZE +1;
  int beatTwoPos = _dTime.getTimeString().substring(1,6).toInt() / 100000.00 * CONTAINER_SIZE +1;
  int beatThreePos = _dTime.getTimeString().substring(2,6).toInt() / 10000.00 * (CONTAINER_SIZE - beatOnePos) + beatOnePos +1;

//  if (beatOnePos != beatOnePosPrev)
//  {
    DrawLineOne(beatOnePosPrev, BLACK);
    DrawLineOne(beatOnePos, WHITE);
//    Serial.println("One");
//  }

//  if (beatTwoPos != beatTwoPosPrev)
//  {
    DrawLineTwo(beatOnePosPrev, beatTwoPosPrev, BLACK);
    DrawLineTwo(beatOnePos, beatTwoPos, WHITE);
//    Serial.println("Two");
//  }

//  if (beatThreePos != beatThreePosPrev)
//  {
    DrawLineThree(beatThreePosPrev, beatTwoPosPrev, BLACK);
    DrawLineThree(beatThreePos, beatTwoPos, WHITE);
//    Serial.println("Three");
//  }

  beatOnePosPrev = beatOnePos;
  beatTwoPosPrev = beatTwoPos;
  beatThreePosPrev = beatThreePos;

  DrawContainer();
  
  //tft.drawFastHLine(OFFSET_H, OFFSET_V + beatOnePos, CONTAINER_SIZE, WHITE);
  //tft.drawFastVLine(OFFSET_H + beatTwoPos, OFFSET_V + beatOnePos, CONTAINER_SIZE - beatOnePos, WHITE);
  //tft.drawFastHLine(OFFSET_H + beatTwoPos, OFFSET_V + beatThreePos, CONTAINER_SIZE - beatTwoPos, WHITE);
}

void DrawLineOne(int pos, uint16_t color)
{
  tft.drawFastHLine(OFFSET_H, OFFSET_V + pos, CONTAINER_SIZE, color);
}

void DrawLineTwo(int posOne, int posTwo, uint16_t color)
{
  tft.drawFastVLine(OFFSET_H + posTwo, OFFSET_V + posOne, CONTAINER_SIZE - posOne, color);
}

void DrawLineThree(int posThree, int posTwo, uint16_t color)
{
  tft.drawFastHLine(OFFSET_H + posTwo, OFFSET_V + posThree, CONTAINER_SIZE - posTwo, color);
}

void DrawText()
{
  String dTime = _dTime.getFormattedDate() + "  " + _dTime.getFormattedTime();
  tft.setCursor(TIME_H, OFFSET_V + CONTAINER_SIZE + SEPERATION);
  tft.println(dTime);
}
