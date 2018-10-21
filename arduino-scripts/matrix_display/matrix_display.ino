// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

// Modified by Aayush Chadha

#include <RGBmatrixPanel.h>

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY     0xD6BA
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int eyeLeftX = 12;
int eyeRightX = 22;
int eyePos = 0;

int state = 0; // 0 for safe, 1 for danger, 2 for ultra danger thingy;

const int eyeX[] = {12,10,8,8,10};
const int eyeY[] = {7,5,6,8,9};
const char str[] PROGMEM = "GO AWAY!   GO AWAY!  GO AWAY!  GO AWAY! GO AWAY!  GO AWAY!  GO AWAY! GO AWAY! GO AWAY!  GO AWAY!";
const char safe[] PROGMEM = "SAFE TO APPROACH";

int16_t    textX         = matrix.width(),
           textMin       = sizeof(str) * -12,
           textMin2      = sizeof(safe) * -6,
           hue           = 0;

void drawSafeToApproach() {

  // Clear any existing drawings.
  matrix.fillScreen(matrix.Color333(0,0,0));
  matrix.drawCircle(16, 10, 10, matrix.Color333(0, 7, 0));
  matrix.fillCircle(16, 10, 10, matrix.Color333(0, 7, 0));

  matrix.drawCircle(11, 8, 3, matrix.Color333(255, 255, 255));
  matrix.fillCircle(11, 8, 3, matrix.Color333(255, 255, 255));
  matrix.drawCircle(21, 8, 3, matrix.Color333(255, 255, 255));
  matrix.fillCircle(21, 8, 3, matrix.Color333(255, 255, 255));
  drawEyes(BLACK,eyePos);
}


void moveEyes()
{
  drawEyes(WHITE,eyePos);
  int r = random(0,10);
  if(r < 5)
  {
    if((++eyePos) > 4)
      eyePos = 0;
  }
  else if((--eyePos) < 0)
      eyePos = 4;
    
  
}
void drawEyes(int color, int pos)
{

  
  matrix.drawRect(eyeX[eyePos],eyeY[eyePos],3, 3, color);
   matrix.fillRect(eyeX[eyePos],eyeY[eyePos],3, 3, color);

   matrix.drawRect(eyeX[eyePos]+10,eyeY[eyePos],3, 3, color);
   matrix.fillRect(eyeX[eyePos]+10,eyeY[eyePos],3, 3, color);
}

void drawDanger() {
  // Clear any existing drawings.
  //matrix.fillScreen(matrix.Color333(0,0,0));
  // Draw white circle
  matrix.drawCircle(16, 10, 10, matrix.Color333(255, 255, 255));
  matrix.fillCircle(16, 10, 10, matrix.Color333(255, 255, 255));

  // Draw smaller red circle
  matrix.drawCircle(16, 10, 8, matrix.Color333(7, 0, 0));
  matrix.fillCircle(16, 10, 8, matrix.Color333(7, 0, 0));

  // Draw white rectangle
  matrix.drawRect(11,9,11, 3, matrix.Color333(255, 255, 255));
  matrix.fillRect(11,9,11, 3, matrix.Color333(255, 255, 255));
 
}

void drawText(String textToPrint, uint16_t color) {

  // draw some text!
  matrix.setCursor(0, 22);    // start at top left, with one pixel of spacing
  matrix.setTextSize(5);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setTextColor(color);
  matrix.println(textToPrint);
  
}

void clearScreen() {

  matrix.fillScreen(matrix.Color333(0,0,0));
  
}

void flashWarning() {
  
  clearScreen();
  
  delay(50);
  int flashes = 20;
  while (flashes >= 0) {

    //Draw circle
    matrix.drawCircle(16, 10, 8, matrix.Color333(7, 0, 0));
    matrix.fillCircle(16, 10, 8, matrix.Color333(7, 0, 0));
    matrix.drawRect(11,9,11, 3, matrix.Color333(255, 255, 255));
    matrix.fillRect(11,9,11, 3, matrix.Color333(255, 255, 255));

    //Draw text
    matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
    matrix.setCursor(textX, 22);
    matrix.print(F2(str));
    // Move text left (w/wrap), increase hue
    if((--textX) < textMin) textX = 32;
    hue += 7;
    if(hue >= 1536) hue -= 1536;

    delay(50);
    clearScreen();

    matrix.drawCircle(16, 10, 10, matrix.Color333(7, 0, 0));
    matrix.fillCircle(16, 10, 10, matrix.Color333(7, 0, 0));
    matrix.drawRect(10,8,13, 4, matrix.Color333(255, 255, 255));
    matrix.fillRect(10,8,13, 4, matrix.Color333(255, 255, 255));
   
    matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
    matrix.setCursor(textX, 22);
    matrix.print(F2(str));
    // Move text left (w/wrap), increase hue
    if((--textX) < textMin) textX = matrix.width();
    hue += 7;
    if(hue >= 1536) hue -= 1536;
    
    delay(50);
    clearScreen();

    matrix.drawCircle(16, 10, 12, matrix.Color333(7, 0, 0));
    matrix.fillCircle(16, 10, 12, matrix.Color333(7, 0, 0));
    matrix.drawRect(9,7,15, 5, matrix.Color333(255, 255, 255));
    matrix.fillRect(9,7,15, 5, matrix.Color333(255, 255, 255));

    matrix.setTextColor(matrix.ColorHSV(hue, 100, 255, true));
    matrix.setCursor(textX, 22);
    matrix.print(F2(str));
    // Move text left (w/wrap), increase hue
    if((--textX) < textMin2) textX = matrix.width();
    hue += 7;
    if(hue >= 1536) hue -= 1536;

    delay(50);
    clearScreen();

    flashes -= 1;

    
    
  }
  
}

int stackOverflowBar = 0;
int previousState = 0;


void displayStackOverflowBar()
{
  for(int i = 0; i< 32;++i)
    for(int j = 21; j< 32; ++j)
      matrix.drawPixel(i,j,BLACK);
  int y = 22;
  int x = 0;
  for(int i = 0; i< stackOverflowBar; ++i)
  {
    matrix.drawPixel(x,y,matrix.Color333(255,10,0));
    if((++x) > 32) {y ++; x = 0;}
    delay(10);
  }
  
}

void scrollSafeText()
{
  for(int i = 0; i< 32;++i)
    for(int j = 21; j< 32; ++j)
      matrix.drawPixel(i,j,BLACK);
      
  matrix.setTextColor(matrix.ColorHSV(hue, 100, 100, true));
    matrix.setCursor(textX, 22);
    matrix.print(F2(safe));
    // Move text left (w/wrap), increase hue
    if((--textX) < textMin2) textX = matrix.width();
    hue += 7;
    if(hue >= 1536) hue -= 1536;
    delay(50);
}
void setup() {
   Serial.begin(9600);
   matrix.begin();
   matrix.setTextWrap(false); // Allow text to run off right edge
   matrix.setTextSize(1);
   drawSafeToApproach();
   randomSeed(analogRead(0));
   
}
unsigned long previousMillis = 0;
unsigned long interval = 3000;
void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    //Take appropriate action based on flag
    switch (incomingByte) 
    {
      case 's': //User went to StackOverflow, increment the bar
        stackOverflowBar++;
        if(state ==1) displayStackOverflowBar();
        break;
      case 'd': // Don't approach 
        drawDanger();
        displayStackOverflowBar();
        state = 1;
        break;
      case 'a': // Safe to approach
        drawSafeToApproach();
        state = 0;
        break;
      case 'g': // GO AWAY!!!1!!
        if(state == 1){
          flashWarning();
          state = 2;
          drawDanger();
          displayStackOverflowBar();
          state = 1;
        }
        break;
    }
  }
    if(state == 0)
    {
      unsigned long currentMillis = millis();
 
      if(currentMillis - previousMillis > interval) { 
        previousMillis = currentMillis;
        moveEyes();
        drawEyes(BLACK,eyePos);
      }
      scrollSafeText();
    } 
}
