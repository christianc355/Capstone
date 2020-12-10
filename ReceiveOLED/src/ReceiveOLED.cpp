/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/christianc/Documents/IoT/Capstone/ReceiveOLED/src/ReceiveOLED.ino"
/*
 * Project Receive OLED
 * Description: LiFi Reciever with OLED
 * Author: Christian Chavez
 * Date: December, 2020
 */

void setup();
void loop();
void readZero();
void readOne();
void decodeData(byte data[8]);
#line 8 "/Users/christianc/Documents/IoT/Capstone/ReceiveOLED/src/ReceiveOLED.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

#include <Adafruit_SSD1306.h>

#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);

const int anodePin = A5;

int anodeRead;
int triggerValue = 100;
unsigned int zeroTime = 20;
unsigned int zeroMin = 10;
unsigned int zeroMax = 30;
unsigned int oneTime = 40;
unsigned int oneMin = 35;
unsigned int oneMax = 50;
unsigned int startTime;
unsigned int endTime;
unsigned int duration;
bool timerState;
int bitZero;
int bitOne;
int bitTwo;
int bitThree;
int bitFour;
int bitFive;
int bitSix;
int bitSeven;

String temp;
char temp_array[6];
byte send_array[8];
int i;
int n;
byte value[8];

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.clearDisplay();
  // display.setRotation(1);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  delay(1000); //system set up time
  display.printf("SYSTEM\nREADY...\n");
  display.display();
  Serial.printf("System Ready...\n");
  delay(3000);
  display.clearDisplay();

}

void loop() {


  anodeRead = analogRead(anodePin);
  //Serial.printf("Anode Read: %i\n", anodeRead); //for testing trigger values only
  
    if (!timerState && anodeRead > triggerValue){ //if timer is off and anode is triggered then continue
      startTime = millis();
      timerState = true;
    }
  
    if (timerState && anodeRead < triggerValue){ //if timer is on and anode is not triggered then continue 
      endTime = millis();
      timerState = false;
      duration = endTime - startTime;
      if(duration > zeroMin && duration < zeroMax){
        readZero();
      }
      else if(duration > oneMin && duration < oneMax){
        readOne();
      }
    }
}

void readZero() {
  send_array[i] = 0;
   //Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
  i++;
  if(i > 7){
    decodeData(send_array);
    i = 0;
  }
}

void readOne() {
  send_array[i] = 1;
   //Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
  i++;
  if(i > 7){
    decodeData(send_array);
    i = 0;
  }
}

void decodeData(byte data[8]){ 
  byte frank = 0x00;
  for(i = 7; i >= 0; i--){
    frank = frank << 1 | data[i];
  }
  bitZero = send_array[0];
  bitOne = send_array[1];
  bitTwo = send_array[2];
  bitThree = send_array[3];
  bitFour = send_array[4];
  bitFive = send_array[5];
  bitSix  = send_array[6];
  bitSeven = send_array[7];

  if(bitZero == 0 && bitOne == 0 && bitTwo == 0 && bitThree == 0 && bitFour == 1 && bitFive == 1 && bitSix == 0 && bitSeven ==1){
    Serial.printf("° Celsius\n");
    display.clearDisplay();
    display.setCursor(0,0);
    display.printf("TEMP\nIN %cC:\n", char(247));
    display.display();
  }
  else{
  Serial.printf("%c", frank);
  display.printf("%c", frank);
  display.display();
  //Serial.printf("Frank: %x, %c, %s\n", frank, frank, frank);
  }
}

