
//                                         (Below double slash line you should not remove it's for your understand purpose if you remove the double slash line, again you should put
//                                                  double slash again)


//        1. Before going to use the programm you must install all the libraries in you arduino version(1.8.13) or (1.8.19) software.
//        2. for this progam (MCUFRIEND_KBV) is importand software(so you can install using arduino software for install (GO to (SKETCH) top left 3rd -> include library - > manage library -> search (MCUFRIEND)))
//        3. (((OR))) you can install manually by (GO to (SKETCH - > include library -> Add zip library -> you browse and choose the zip file location of libray)
//        4. <TIME.H> and  <spi> library is inbuilt so you don't need to install..



//        Below i delcare libary we used:
#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
#include <Time.h>
#include <SPI.h>



//        Below we create a class name for our library as object
MCUFRIEND_kbv tft;




//        This is the color of waveform we declare so that you can change what ever color you want with this given color below
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF



//        here we declare the variable value for our programss
int xPos = 25, xPosPrev = 25;
//int xPos1 = 30, xPosPrev1 = 30;
int n = 0;
int graphHeightPrev, graphHeightPrev1 = 0;
int16_t ht = 6, top = 3, line, lines = 5, scroll;




//        setup is for to declare the variable value is going to work as output or input pins and also we initialize the dispaly properties and begin the serial communications
int state = 0;
void setup() {
//Serial.begin(115200);
Serial.begin(9600);
Serial1.begin(9600);
tft.reset();
uint16_t id = tft.readID();
tft.begin(id);
tft.setRotation(1);
tft.fillScreen(BLACK);
tft.setTextColor(WHITE);

tft.drawLine(20, 30, 20, 300, WHITE);
tft.setTextSize(1.5);
tft.setTextColor(WHITE);
tft.setCursor(30, 50);
tft.print("1024");
tft.setTextSize(1.5);
tft.setTextColor(WHITE);
tft.setCursor(30, 260);
tft.print("-1024");
}


//          void loop will run the program continouslyy
          
void loop() {
  if(Serial1.available()>0){ // Checks whether data is comming from the serial port
    state = Serial1.read();
}
//        Here the A7 and A11 are input pins to read the sensor output values
//Serial.println(Serial1.read());
//int val = Serial1.read();
  int sensor = state;
//  int sensor1 = analogRead(A11);

  
//        Here we map the sensor value into desire value for our graph representation
  int graphHeight = map(sensor, 0, 450, 150, 250);
//  int graphHeight1 = map(sensor1, 0, 1023, 100, 150);

  
//        Here we draw the graphheight, width and color of our waveforms
  tft.drawLine(xPosPrev, tft.height() - graphHeightPrev, xPos, tft.height() - graphHeight, GREEN);
//  tft.drawLine(xPosPrev1, tft.height() - graphHeightPrev1, xPos1, tft.height() - graphHeight1, YELLOW);
  graphHeightPrev = graphHeight;
//  graphHeightPrev1 = graphHeight1;

  
//        Below we declare the once our waveform reach the extreme size of our disply below program reset the dispaly.
  if (xPos >= 480) { //&& xPos1 
  xPos = 20;
//  xPos1 = 30;
  xPosPrev = 20;
//  xPosPrev1 = 30;
  tft.fillScreen(BLACK);
  tft.setCursor(180, 10);
  tft.print("PHONOCARDIOGRAM");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(120, 300);
  tft.print("BY ARAVIND (M.S)");
  tft.drawLine(20, 30, 20, 300, WHITE);
  tft.setTextSize(1.5);
  tft.setTextColor(WHITE);
  tft.setCursor(30, 50);
  tft.print("1024");
  tft.setTextSize(1.5);
  tft.setTextColor(WHITE);
  tft.setCursor(30, 260);
  tft.print("-1024");
}


//        in else conditon we increment the value of xpos value for next iteratin of our programms
  else {
  xPosPrev = xPos;
//  xPosPrev1 = xPos1;
  xPos++;
//  xPos1++;
}
  delay(16);
}
