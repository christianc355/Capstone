/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/LaserTest/src/LaserTest.ino"
/*
 * Project LaserTest
 * Description: Testing Laser Stuff
 * Author: Christian Chavez
 * Date: 11-23-2020
 */


void setup();
void loop();
void beamZero();
void beamOne();
#line 9 "/Users/christianc/Documents/IoT/Capstone/LaserTest/src/LaserTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

// bool laserRead;
// int laserWrite;

// void setup() {

//   pinMode(A0, OUTPUT);
//   pinMode(A1, INPUT);

// }


// void loop() {

//   digitalWrite(A0, HIGH);
//   // delay(10);
//   // digitalWrite(A0, LOW);
//   // delay(10);
//   laserRead = digitalRead(A1);
//   Serial.printf("Laser Read: %i\n",laserRead);

// }

//incrament through array
//if value = 0 void show 0
//if value = 1 void show 1


int array[] = {1, 0, 1, 0, 0};
// int array[] = {134, 2342, 5125, 72456, 235654};
int i;

unsigned int zeroTime = 500;
unsigned int oneTime = 1000;
unsigned int zeroCurrentTime;
unsigned int zeroLastTime;
unsigned int oneCurrentTime;
unsigned int oneLastTime;
int anodeRead;

const int laserPin = A0;
const int anodePin = A4;

void setup() {

  Serial.begin(9600);

  pinMode(laserPin, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(anodePin, INPUT);

}

void loop() {

  digitalWrite(A1, HIGH);

  anodeRead = analogRead(anodePin);
  

  for(i = 0; i <= 4; i++){

    if(array[i] == 0){

      beamZero();
      
    }
    else if(array[i] == 1){

      beamOne();

    }

  }

}

void beamZero() {

  // Serial.printf("Array value is ZERO\n");
  digitalWrite(laserPin, HIGH);
  Serial.printf("Anode Read: %i\n", anodeRead);
  delay(zeroTime);
  digitalWrite(laserPin, LOW);
  delay(25);
    // zeroCurrentTime = millis();
  // if(zeroCurrentTime - zeroLastTime < zeroTime){
    
  //   digitalWrite(laserPin, HIGH);

  // }
  // else{

  //   digitalWrite(laserPin, LOW);

  // }

}

void beamOne() {

  //Serial.printf("Array value is ONE\n");
  digitalWrite(laserPin, HIGH);
  Serial.printf("Anode Read: %i\n", anodeRead);
  delay(oneTime);
  digitalWrite(laserPin, LOW);
  delay(25);
  // oneCurrentTime = millis();
  // if(oneCurrentTime - oneLastTime < oneTime){

  //   digitalWrite(laserPin, HIGH);

  // }
  // else{

  //   digitalWrite(laserPin, LOW);

  // }

}