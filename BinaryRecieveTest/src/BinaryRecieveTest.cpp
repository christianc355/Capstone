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
void decodeData(byte decode_data[8]);
#line 8 "/Users/christianc/Documents/IoT/Capstone/BinaryRecieveTest/src/BinaryRecieveTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

const int anodePin = A5;

int anodeRead;
int triggerValue = 10;
unsigned int zeroMin = 300;
unsigned int zeroMax = 700;
unsigned int oneMin = 800;
unsigned int oneMax = 1200;
unsigned int startTime;
unsigned int endTime;
unsigned int duration;
bool timerState;

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
   Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
  i++;
  if(i > 7){
    decodeData(send_array);
    i = 0;
  }
}

void readOne() {
  send_array[i] = 1;
   Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
  i++;
  if(i > 7){
    decodeData(send_array);
    i = 0;
  }
}

// void decodeData(byte decode_data[8]){ //working to decode data
//   for(i = 0; i < 8; i++){
//     //Serial.printf("decode_data[i] %i i: %i\n", decode_data[i], i);
//     Serial.printf("%i", decode_data[i]);
//   }
//   Serial.printf("\n"); //moves to next line after above code is finished
// }


void decodeData(byte decode_data[8]){ //working to decode data
  for(i = 0; i < 8; i++){
    //Serial.printf("decode_data[i] %i i: %i\n", decode_data[i], i);
    Serial.printf("%i", decode_data[i]);
  }
  Serial.printf("\n"); //moves to next line after above code is finished
  value[i] = decode_data[1]  << i | 0x01;
  Serial.printf("Value[i] %x\n", value[0]);
}



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
