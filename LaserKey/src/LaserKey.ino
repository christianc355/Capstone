/*
 * Project: Laser Key
 * Description: LiFi Key
 * Author: Christian Chavez
 * Date: December, 2020
 */

SYSTEM_MODE(SEMI_AUTOMATIC);
//revert to here before OLED

#include <Adafruit_SSD1306.h>

#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);

#include <OneButton.h>

const int laserPin = A5;
const int buttonPin = A2;
const int extraButtonPin = A3;

 OneButton button1(buttonPin, false, false);
 OneButton button2(extraButtonPin, false, false);

 int array[] = {1, 1, 0, 1, 0};
 int extraArray[] = {0, 0, 1, 0, 1};
 // int array[] = {134, 2342, 5125, 72456, 235654};
 int i;

unsigned int zeroTime = 10;//works with ReceiverKeyOLED.ino
unsigned int oneTime = 20; 
unsigned int offDelay = 50;
// unsigned int zeroTime = 1000;//works with ReceiverKeyOLED.ino
// unsigned int oneTime = 2000; 
// unsigned int offDelay = 500;
// unsigned int zeroTime = 100;//works with ReceiverKey.ino
// unsigned int oneTime = 200; 
// unsigned int offDelay = 50;
unsigned int zeroCurrentTime;
unsigned int zeroLastTime;
 unsigned int oneCurrentTime;
 unsigned int oneLastTime;

 bool buttonState;
 bool extraButtonState;



 void setup() {

   Serial.begin(9600);

   pinMode(laserPin, OUTPUT);
   pinMode(A1, OUTPUT);
   pinMode(buttonPin, INPUT_PULLDOWN);
   pinMode(extraButtonPin, INPUT_PULLDOWN);
   pinMode(A1, OUTPUT); //used for testing 

   button1.attachClick(click1);
   button1.setClickTicks(250);
   button2.attachClick(click2);
   button2.setClickTicks(250);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setCursor(0,0);
  // display.setRotation(1);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  delay(1000);


  Serial.printf("System Ready...");
  display.printf("LASER\nSYSTEM\nREADY...\n");
  display.display();

 }

 void loop() {

   button1.tick();
   button2.tick();
   digitalWrite(A1, HIGH);
   Serial.printf("Button State: %i\n", buttonState);


   if(buttonState){
     display.clearDisplay();
     display.setCursor(0,0);
     display.printf("SENDING\nCONFIRMED\nDATA...");
     display.display();

   for(i = 0; i <= 4; i++){


    if(array[i] == 0){
       
       beamZero();

    }
    else if(array[i] == 1){

       beamOne();

     }

       if(i < 4){

        buttonState = false;
       }
       if(i == 4){
        display.clearDisplay();
        display.setCursor(0,0);
        display.printf("DATA\nSENT");
        display.display();
       }
     }
   }

   if(extraButtonState){
     display.clearDisplay();
     display.setCursor(0,0);
     display.printf("SENDING\nINVALID\nDATA...");
     display.display();

     for(i = 0; i <= 4; i++){

       if(extraArray[i] == 0){

         beamZero();

       }
       else if(extraArray[i] == 1){

         beamOne();

       }

       if(i < 4){

         extraButtonState = false;

       }
       if(i == 4){
        display.clearDisplay();
        display.setCursor(0,0);
        display.printf("DATA\nSENT");
        display.display();
       }       
     }
   }
   
 }

void beamZero() {

  // Serial.printf("Array value is ZERO\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ZERO\n");
  delay(zeroTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);

}

void beamOne() {

  //Serial.printf("Array value is ONE\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ONE\n");
  delay(oneTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);

}

 void click1(){

   buttonState = !buttonState;

 }

 void click2(){

   extraButtonState = !extraButtonState;

 } 