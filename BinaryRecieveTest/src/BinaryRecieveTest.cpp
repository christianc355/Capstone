/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/BinaryRecieveTest/src/BinaryRecieveTest.ino"
/*
 * Project BinaryRecieveTest
 * Description: LiFi Reciever 2.0
 * Author: Christian Chavez
 * Date: December, 2020
 */

void setup();
void loop();
#line 8 "/Users/christianc/Documents/IoT/Capstone/BinaryRecieveTest/src/BinaryRecieveTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

const int anodePin = A5;

int anodeRead;
int triggerValue = 10;
unsigned int zeroMin = 30;
unsigned int zeroMax = 70;
unsigned int oneMin = 80;
unsigned int oneMax = 120;
unsigned int startTime;
unsigned int endTime;
unsigned int duration;
bool timerState;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);
  delay(1000); //system set up time
  Serial.printf("System Ready...\n");

}


void loop() {

  anodeRead = analogRead(anodePin);

  if (!timerState && anodeRead > triggerValue){ //if timer is off and anode is triggered then continue
    startTime = millis();
    timerState = true;
  }

  if (timerState && anodeRead < triggerValue){ //if timer is on and anode is not triggered then continue 
    endTime = millis();
    timerState = false;
    duration = endTime - startTime;

    if(duration > zeroMin && duration < zeroMax){
      Serial.printf("Zero");
    }
    else if(duration > oneMin && duration < oneMax){
      Serial.printf("One");
    }
  }

}