/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/ReceiveTest/src/ReceiveTest.ino"


/*
 * Project ReceiveTest
 * Description: LiFi Receiver
 * Author: Christian Chavez
 * Date:
 */

void setup();
void loop();
void receiveClick();
#line 10 "/Users/christianc/Documents/IoT/Capstone/ReceiveTest/src/ReceiveTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <OneButton.h>

const int anodePin = A5;
const int buttonPin = D5;

OneButton receiveButton(buttonPin, false, false);
// #define bitRead(value, bit) (((value) >> (bit)) & 0x01)
// #define bitSet(value, bit) ((value) |= (1UL << (bit)))
// #define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
// #define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

int anodeRead; 
int triggerValue = 10;
unsigned int zeroTime = 5;
unsigned int oneTime = 10;
unsigned int startTime;
unsigned int endTime;
unsigned int duration;
bool timerState;
int array[6];
int arrayMax = 5;
int i = 0;
int bitZero; //maybe make these bools 
int bitOne; 
int bitTwo;
int bitThree;
int bitFour;
int n;
bool buttonState;
bool printState = false;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(D7, OUTPUT); //for testing only
  receiveButton.attachClick(receiveClick);
  receiveButton.setClickTicks(250);
  delay(1000); //set up time
  Serial.printf("System Ready...");

}
void loop() {

  receiveButton.tick();
  
  anodeRead = analogRead(anodePin);
   //Serial.printf("Anode: %i\n", anodeRead); //used for testing
  
  if (i > 5){ //do not change
   i = 1; //do not change 
  }

  if (!timerState && anodeRead > triggerValue){ //if timer is not running and anode is triggered then run
    startTime = millis();
    timerState = true;
    i++; //sets i = to 1 right away
  }

  if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
    endTime = millis();
    timerState = false;
    duration = endTime - startTime;

    if(duration > 3 && duration < 7){
      array[i] = 0;
      Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
    }
    else if(duration > 8 && duration < 12){
      array[i] = 1;
      Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
    }
  }

    bitZero = array[1];
    bitOne = array[2];
    bitTwo = array[3];
    bitThree = array[4];
    bitFour = array[5];

  if(bitZero == 0 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 1){
    Serial.printf("Yellow button\n");
    analogWrite(D7, 20); //for testing only
  }
  else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
    Serial.printf("Blue button\n");
    analogWrite(D7, 255); //for testing only
  }
}


void receiveClick() {

  buttonState = !buttonState;
  Serial.printf("Button State: %i\n", buttonState);

}


// SYSTEM_MODE(SEMI_AUTOMATIC);

// #include <OneButton.h>

// const int anodePin = A5;
// const int buttonPin = D5;

// OneButton receiveButton(buttonPin, false, false);
// // #define bitRead(value, bit) (((value) >> (bit)) & 0x01)
// // #define bitSet(value, bit) ((value) |= (1UL << (bit)))
// // #define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
// // #define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// int anodeRead; 
// int triggerValue = 10;
// unsigned int zeroTime = 5;
// unsigned int oneTime = 10;
// unsigned int startTime;
// unsigned int endTime;
// unsigned int duration;
// bool timerState;
// int array[6];
// int arrayMax = 5;
// int i = 0;
// int bitZero; //maybe make these bools 
// int bitOne; 
// int bitTwo;
// int bitThree;
// int bitFour;
// int n;
// bool buttonState;
// bool printState = false;

// void setup() {

//   Serial.begin(9600);
//   pinMode(anodePin, INPUT);
//   pinMode(buttonPin, INPUT_PULLDOWN);
//   pinMode(D7, OUTPUT); //for testing only
//   pinMode(D6, OUTPUT);
//   receiveButton.attachClick(receiveClick);
//   receiveButton.setClickTicks(250);
//   delay(1000); //set up time
//   Serial.printf("System Ready...");

// }
// void loop() {

//   receiveButton.tick();
  
//   anodeRead = analogRead(anodePin);
//    //Serial.printf("Anode: %i\n", anodeRead); //used for testing
  
//   if (i > 5){ //do not change
//    i = 1; //do not change 
//   }

//   if (!timerState && anodeRead > triggerValue){ //if timer is not running and anode is triggered then run
//     startTime = millis();
//     timerState = true;
//     i++; //sets i = to 1 right away
//   }

//   if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
//     endTime = millis();
//     timerState = false;
//     duration = endTime - startTime;

//     if(duration > 3 && duration < 7){
//       array[i] = 0;
//       Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
//     }
//     else if(duration > 8 && duration < 12){
//       array[i] = 1;
//       Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
//     }
//   }

//     bitZero = array[1];
//     bitOne = array[2];
//     bitTwo = array[3];
//     bitThree = array[4];
//     bitFour = array[5];

//   if(i = 5){

//     if(bitZero == 0 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 1){
//       Serial.printf("Yellow button\n");
//       analogWrite(D7, 0); //for testing only
//       analogWrite(D6, 255);
//       buttonState = !buttonState;
//       i = 0;
//     }
//     else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
//       Serial.printf("Blue button\n");
//       analogWrite(D7, 255); //for testing only
//       analogWrite(D6, 0);
//       buttonState = !buttonState;
//       i = 0;
//     }
//   }
// }


// void receiveClick() {

//   buttonState = !buttonState;
//   Serial.printf("Button State: %i\n", buttonState);

// }