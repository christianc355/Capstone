/*
 * Project BinaryRecieveTest
 * Description: LiFi Reciever 2.0
 * Author: Christian Chavez
 * Date: December, 2020
 */

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
byte data[8];
byte send_array[8];
int i;
int n;

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
        //Serial.printf("Zero");
        readZero();
       // Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
      }
      else if(duration > oneMin && duration < oneMax){
        //Serial.printf("One");
        readOne();
        // Serial.printf("send_array[i]: %i i: %i\n", send_array[i], i);
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

void decodeData(byte decode_data[8]){
  for(i = 0; i < 8; i++){
    Serial.printf("decode_data[i] %i\n", decode_data[i]);
  }

}