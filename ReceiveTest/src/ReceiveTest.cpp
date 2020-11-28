/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/ReceiveTest/src/ReceiveTest.ino"
/*
 * Project ReceiveTest
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/Users/christianc/Documents/IoT/Capstone/ReceiveTest/src/ReceiveTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

// #define bitRead(value, bit) (((value) >> (bit)) & 0x01)
// #define bitSet(value, bit) ((value) |= (1UL << (bit)))
// #define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
// #define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


int anodeRead; 
int triggerValue = 100;


unsigned int zeroTime = 5000;
unsigned int oneTime = 10000;

unsigned int startTime;
unsigned int endTime;
unsigned int duration;
bool timerState;

int array[1000];
int arrayMax = 5;
int i;

const int anodePin = A1;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);

}

void loop() {
  
  anodeRead = analogRead(anodePin);

  if (!timerState && anodeRead > triggerValue){ //if timer is not running and anode is triggered then run
    startTime = millis();
    timerState = true;
    i++;
  }
  if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
    endTime = millis();
    timerState = false;
    duration = endTime - startTime;
      if(duration > 3 && duration < 7){
       // Serial.printf("ZERO\n");
        array[i] = 0;
        Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
      }
      else if(duration > 8 && duration < 12){
       // Serial.printf("ONE\n");
        array[i] = 1;
        Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
      }
  //Serial.printf ("Duration: %i\n", duration);
  
  }

}
