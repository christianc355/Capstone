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
void readZero();
void readOne();
void decodeData(byte data[8]);
#line 8 "/Users/christianc/Documents/IoT/Capstone/BinaryRecieveTest/src/BinaryRecieveTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

const int anodePin = A5;

int anodeRead;
int triggerValue = 100;
unsigned int zeroMin = 30;
unsigned int zeroMax = 70;
unsigned int oneMin = 80;
unsigned int oneMax = 120;
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
  delay(1000); //system set up time
  Serial.printf("System Ready...\n");

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
  }
  else{
  Serial.printf("%c", frank);
  //Serial.printf("Frank: %x, %c, %s\n", frank, frank, frank);
  }
}

// void decodeData(byte decode_data[8]){ //working to decode data
//   for(i = 0; i < 8; i++){
//     //Serial.printf("decode_data[i] %i i: %i\n", decode_data[i], i);
//     Serial.printf("%i", decode_data[i]);
//   }
//   Serial.printf("\n"); //moves to next line after above code is finished
// }




// void decodeData(byte decode_data[8]){ //working to decode data
//   for(i = 0; i < 8; i++){
//     //Serial.printf("decode_data[i] %i i: %i\n", decode_data[i], i);
//     Serial.printf("%i", decode_data[i]);
//   }
//   Serial.printf("\n"); //moves to next line after above code is finished
// }

// void decodeData(byte decode_data[8]){
//   for(n = 0; n < 5; n++){
//     for(i = 8; i > 0; i--){
//       temp_array[n] = decode_data[i] << i | 0x01;
//       Serial.printf("temp_array: %x decode_data[i] %i i: %i n: %i\n", temp_array[n], decode_data[i], i , n);
//     }
//   }
// }


// void decodeData(byte decode_data[8]){
//   for(n = 0; n < 5; n++){
//     for(i = 8; i > 0; i--){
//       temp_array[n] = decode_data[i] << i | 0x01;
//       Serial.printf("temp_array: %x decode_data[i] %i i: %i n: %i\n", temp_array[n], decode_data[i], i , n);
//     }
//   }
// }
