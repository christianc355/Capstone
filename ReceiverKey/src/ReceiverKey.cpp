/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/ReceiverKey/src/ReceiverKey.ino"


/*
 * Project ReceiveTest
 * Description: LiFi Receiver
 * Author: Christian Chavez
 * Date:
 */

void setup();
void loop();
void displayAlarm();
#line 10 "/Users/christianc/Documents/IoT/Capstone/ReceiverKey/src/ReceiverKey.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <Adafruit_SSD1306.h>

#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);

const int anodePin = A5;



int anodeRead; 
int triggerValue = 100;
unsigned int zeroTime = 300;
unsigned int zeroMin = 100;
unsigned int zeroMax = 500;
unsigned int oneTime = 800;
unsigned int oneMin = 600;
unsigned int oneMax = 1000;
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
bool printState = false;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);

  pinMode(D7, OUTPUT); //for testing only

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setRotation(1);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  delay(1000); //system set up time
  Serial.printf("System Ready...\n");

}
void loop() {

  anodeRead = analogRead(anodePin);
  //Serial.printf("Anode: %i\n", anodeRead); //used for testing
  
  if (i > 5){ //do not change
    displayAlarm();
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

    if(duration > zeroMin && duration < zeroMax){
      array[i] = 0;
      Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
    }
    else if(duration > oneMin && duration < oneMax){
      array[i] = 1;
      Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
    }
  }


}

void displayAlarm() {
    bitZero = array[1];
    bitOne = array[2];
    bitTwo = array[3];
    bitThree = array[4];
    bitFour = array[5];

  if(bitZero == 0 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 1){
    display.printf("System Blue Locked");
    display.display();
    //Serial.printf("Yellow button\n");
    analogWrite(D7, 20); //for testing only
  }
  else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
    display.printf("System Yellow Locked");
    display.display();
    //Serial.printf("Blue button\n");
    analogWrite(D7, 255); //for testing only
  }
}