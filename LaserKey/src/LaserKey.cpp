/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/LaserKey/src/LaserKey.ino"
/*
 * Project: Laser Key
 * Description: LiFi Key
 * Author: Christian Chavez
 * Date: December, 2020
 */

void setup();
void loop();
void beamZero();
void beamOne();
void click1();
void click2();
#line 8 "/Users/christianc/Documents/IoT/Capstone/LaserKey/src/LaserKey.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);


#include <OneButton.h>

const int laserPin = A5;
const int buttonPin = D5;
const int extraButtonPin = D6;

 OneButton button1(buttonPin, false, false);
 OneButton button2(extraButtonPin, false, false);

 int array[] = {1, 1, 0, 1, 1};
 int extraArray[] = {0, 0, 1, 0, 0};
 // int array[] = {134, 2342, 5125, 72456, 235654};
 int i;

// unsigned int zeroTime = 500;//works with ReceiverKeyOLED.ino
// unsigned int oneTime = 1000; 
// unsigned int offDelay = 250;
unsigned int zeroTime = 1000;//works with ReceiverKeyOLED.ino
unsigned int oneTime = 2000; 
unsigned int offDelay = 500;
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

 }

 void loop() {

   button1.tick();
   button2.tick();
   digitalWrite(A1, HIGH);
   Serial.printf("Button State: %i\n", buttonState);


   if(buttonState){

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
     }
   }

   if(extraButtonState){
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