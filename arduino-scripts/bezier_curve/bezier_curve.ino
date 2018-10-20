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

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void drawBezierCurve(int startX, int startY, int endX, int endY) {
  double midPoint = (endX - startX)/2;
  double splineHeight = startY*1.9;
//
//  Serial.println(splineHeight);
//  
//  double startPositionVectorX = startX - midPoint;
//  double startPositionVectorY = startY - splineHeight;
//
//  Serial.println(startPositionVectorY);
//
//  double endPositionVectorX = endX - midPoint;
//  double endPositionVectorY = endY - splineHeight;
//
//  Serial.println(endPositionVectorY);
  
  double t = 0.0;
  double t_step = 0.01;
  while (t <= 1) {

    double pixelToColorX = pow((1-t),2)*startX + 2*(1-t)*t*midPoint + pow(t,2)*endX;
    double pixelToColorY = pow((1-t),2)*startY + 2*(1-t)*t*ceil(splineHeight) + pow(t,2)*endY;


    Serial.println(pixelToColorX);
    Serial.println(pixelToColorY);
    Serial.println(t);
    
    matrix.drawPixel(ceil(pixelToColorX), ceil(pixelToColorY), matrix.Color333(255,255,255));
   
    t = t+t_step;
  }
}

void drawSafeToApproach() {

  matrix.drawCircle(16, 10, 10, matrix.Color333(7, 7, 0));
  matrix.fillCircle(16, 10, 10, matrix.Color333(7, 7, 0));
  delay(500);

  // draw eye 1
  matrix.drawCircle(12, 5, 2, matrix.Color333(0,0,0));
  matrix.fillCircle(12, 5, 2, matrix.Color333(255,255,255));

  // draw eye 2
  matrix.drawCircle(20, 5, 2, matrix.Color333(0,0,0));
  matrix.fillCircle(20, 5, 2, matrix.Color333(255,255,255));

  // draw bezier curve using a spline in the middle of the two points
  drawBezierCurve(8, 12, 26, 12);
//  // fill a violet circle
//  matrix.fillCircle(21, 21, 10, matrix.Color333(7, 0, 7));
//  delay(500);
//
//  // fill the screen with 'black'
//  matrix.fillScreen(matrix.Color333(0, 0, 0));
//
}

void drawDanger() {
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
   //drawSafeToApproach();
   drawDanger();
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
    }
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
        }
}
