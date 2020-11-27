/*
 * Project ReceiveTest
 * Description:
 * Author:
 * Date:
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


int anodeRead; 
int anodeBit;
int triggerValue = 700;

unsigned int startTime;
unsigned int stopTime;

unsigned int zeroTime = 5000;
unsigned int oneTime = 10000;
unsigned int timerValue;

const int anodePin = A1;

void setup() {

  Serial.begin(9600);
  pinMode(anodePin, INPUT);
  

}

void loop() {
  
  anodeRead = analogRead(anodePin);
  timerValue = startTime - stopTime;
  
  // Serial.printf("Anode Read: %i\n", anodeRead);
  // Serial.printf("Start Time: %i Stop Time: %i Timer Value: %i\n", startTime, stopTime, timerValue);


  if(anodeRead > triggerValue){
    startTime = millis();
  }
  else if (anodeRead < triggerValue){
    stopTime = millis();

    if(startTime - stopTime < zeroTime){
      Serial.printf("Zero Time\n");
      delay(1000);
    }
    else if(startTime - stopTime < oneTime){
      Serial.printf("One Time\n");
      delay(1000);
    }
  }
}  

