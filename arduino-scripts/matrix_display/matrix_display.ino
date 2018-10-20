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

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
int eyeLeftX = 12;
int eyeRightX = 22;
int state = 0; // 0 for safe, 1 for danger, 2 for ultra danger thingy;
//void drawBezierCurve(int startX, int startY, int endX, int endY) {
//  double midPoint = (endX - startX)/2;
//  double splineHeight = startY*1.9;
////
////  Serial.println(splineHeight);
////  
////  double startPositionVectorX = startX - midPoint;
////  double startPositionVectorY = startY - splineHeight;
////
////  Serial.println(startPositionVectorY);
////
////  double endPositionVectorX = endX - midPoint;
////  double endPositionVectorY = endY - splineHeight;
////
////  Serial.println(endPositionVectorY);
//  
//  double t = 0.0;
//  double t_step = 0.01;
//  while (t <= 1) {
//
//    double pixelToColorX = pow((1-t),2)*startX + 2*(1-t)*t*midPoint + pow(t,2)*endX;
//    double pixelToColorY = pow((1-t),2)*startY + 2*(1-t)*t*ceil(splineHeight) + pow(t,2)*endY;
//
//
//    Serial.println(pixelToColorX);
//    Serial.println(pixelToColorY);
//    Serial.println(t);
//    
//    matrix.drawPixel(ceil(pixelToColorX), ceil(pixelToColorY), matrix.Color333(255,255,255));
//   
//    t = t+t_step;
//  }
//}

void drawSafeToApproach() {

  // Clear any existing drawings.
  matrix.fillScreen(matrix.Color333(0,0,0));

  matrix.drawCircle(16, 10, 10, matrix.Color333(0, 7, 0));
  matrix.fillCircle(16, 10, 10, matrix.Color333(0, 7, 0));

  // Write text inside circle
//  matrix.setCursor(8, 6);
//  matrix.setTextSize(1);
//  matrix.setTextWrap(false);
//
//  matrix.setTextColor(matrix.Color333(255, 255, 255));
//  matrix.println("Go!");
   matrix.drawCircle(11, 8, 3, matrix.Color333(255, 255, 255));
   matrix.fillCircle(11, 8, 3, matrix.Color333(255, 255, 255));

   matrix.drawCircle(21, 8, 3, matrix.Color333(255, 255, 255));
   matrix.fillCircle(21, 8, 3, matrix.Color333(255, 255, 255));
   drawEyes(BLACK);
}

void drawEyes(int color)
{
  matrix.drawRect(eyeRightX,7,3, 3, color);
   matrix.fillRect(eyeRightX,7,3, 3, color);

   matrix.drawRect(eyeLeftX,7,3, 3, color);
   matrix.fillRect(eyeLeftX,7,3, 3, color);
}

void drawDanger() {
  // Clear any existing drawings.
  matrix.fillScreen(matrix.Color333(0,0,0));
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
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setTextColor(color);
  matrix.println(textToPrint);
  
}

void clearScreen() {

  matrix.fillScreen(matrix.Color333(0,0,0));
  
}

void flashWarning() {
  
  clearScreen();
  
  int flashes = 50;
  while (flashes >= 0) {

    matrix.drawCircle(16, 10, 8, matrix.Color333(7, 0, 0));
    matrix.fillCircle(16, 10, 8, matrix.Color333(7, 0, 0));
    matrix.drawRect(11,9,11, 3, matrix.Color333(255, 255, 255));
    matrix.fillRect(11,9,11, 3, matrix.Color333(255, 255, 255));
    delay(500);
    matrix.drawCircle(16, 10, 10, matrix.Color333(7, 0, 0));
    matrix.fillCircle(16, 10, 10, matrix.Color333(7, 0, 0));

    matrix.drawRect(11,9,11, 3, matrix.Color333(255, 255, 255));
    matrix.fillRect(11,9,11, 3, matrix.Color333(255, 255, 255));
  
    matrix.setCursor(0, 22);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  
    matrix.setTextColor(matrix.Color333(255, 255, 255));
    matrix.println("Be gone!");
    delay(500);
    clearScreen();

    flashes -= 1;
    
  }
}

int stackOverflowBarX = 0;
int stackOverflowBarY = 28;


void incrementStackOverflowBar()
{
  matrix.drawPixel(stackOverflowBarX,stackOverflowBarY,matrix.Color333(255,10,0));
  stackOverflowBarX++;
  if(stackOverflowBarX == 32)
  {
    stackOverflowBarX = 0;
    stackOverflowBarY ++;
  }
}

void setup() {
   Serial.begin(9600);
   matrix.begin();
   // Default start state
   drawSafeToApproach();
   randomSeed(analogRead(4));
}

void loop() {
  // Do nothing -- image doesn't change
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    //Take appropriate action based on flag
    switch (incomingByte) 
    {
      case 115: //s
        incrementStackOverflowBar();
        break;
      case 100: // Danger
        drawDanger();
        state = 1;
        break;
      case 102: // Safe
        drawSafeToApproach();
        state = 0;
        break;
      case 103: //key word detected
        flashWarning();
        break;
    }
     // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
          
}
