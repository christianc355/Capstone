/*
 * Project ReceiveTest
 * Description: LiFi Receiver
 * Author: Christian Chavez
 * Date:
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include <OneButton.h>


const int anodePin = A1;
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

int array[100];
int arrayMax = 5;
int i;

int bitZero; //maybe make these bools 
int bitOne; 
int bitTwo;
int bitThree;
int bitFour;
int n;

bool buttonState;
bool printState;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);

  receiveButton.attachClick(receiveClick);
  receiveButton.setClickTicks(250);


}

void loop() {

  receiveButton.tick();
  
  anodeRead = analogRead(anodePin);
  //Serial.printf("Anode: %i\n", anodeRead); //used for testing

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
       // Serial.printf("Yellow button\n");
    }
    else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
      //  Serial.printf("Blue button\n");
    }

}

void receiveClick() {

  buttonState = !buttonState;
  Serial.printf("Button State: %i\n", buttonState);

}
