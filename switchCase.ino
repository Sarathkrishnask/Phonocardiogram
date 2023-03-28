/*
  Switch statement

  Demonstrates the use of a switch statement. The switch statement allows you
  to choose from among a set of discrete values of a variable. It's like a
  series of if statements.

  To see this sketch in action, put the board and sensor in a well-lit room,
  open the Serial Monitor, and move your hand gradually down over the sensor.

  The circuit:
  - photoresistor from analog in 0 to +5V
  - 10K resistor from analog in 0 to ground

  created 1 Jul 2009
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SwitchCase
*/
#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
TMRpcm audio;

SoftwareSerial hc_05(5,4);
#define SD_CSPin 10
int pwm_ = 9; 
int val = 0;
int file_number = 0;
char filePrefixname[50] = "spy";
char exten[10] = ".wav";
int led_out = 5;
const int mic_pin = A5;
int lm35_pin = A0;
const int sample_rate = 84000;
char file_name[50];
int sensorMin = 0;      // sensor minimum, discovered through experiment
const byte interruptPin = 2;
const byte interruptPin_ = 3;
const byte ledPin = 13;
int range=0;
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  hc_05.begin(9600);
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(interruptPin_, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, LOW);
  attachInterrupt(digitalPinToInterrupt(interruptPin_), blink_, LOW);
    pinMode(mic_pin, INPUT);
    pinMode(pwm_, OUTPUT);


  //  pinMode(recordLed, OUTPUT);
//  Serial.println("loading... SD card");
//  if (!SD.begin(SD_CSPin)) {
//    Serial.println("An Error has occurred while mounting SD");
//  }
//  while (!SD.begin(SD_CSPin)) {
//    Serial.print(".");
//    delay(500);
//  }
  audio.CSPin = SD_CSPin;
}

void loop() {
  int val = analogRead(A5);
  Serial.println(val);
  hc_05.write(val);
  char fileSlNum[20] = "";
  itoa(file_number, fileSlNum, 10);
  char file_name[50] = "";
  strcat(file_name, filePrefixname);
  strcat(file_name, fileSlNum);
  strcat(file_name, exten);
//  if(val >400){
    analogWrite(pwm_, val / 120);
//    }/
  
  switch (range) {
    case 1:    // your hand is close to the sensor
      if(sensorMin==0){
        audio.startRecording(file_name, sample_rate, mic_pin);
        sensorMin=1;
      }
      break;
    case 2:    // your hand is nowhere near the sensor
      if(sensorMin==1){
        audio.stopRecording(file_name);
        file_number++;
        sensorMin=0;
      }
      break;
  }
  delay(100);        // delay in between reads for stability
}
void blink(){
  range=1;
}
void blink_(){
  range=2;
}
