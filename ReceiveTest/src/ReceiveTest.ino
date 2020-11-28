/*
 * Project ReceiveTest
 * Description:
 * Author:
 * Date:
 */

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
  }
  if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
  endTime = millis();
  timerState = false;
  duration = endTime - startTime;
    if(duration > 3 && duration < 7){
      Serial.printf("ZERO\n");
    }
    else if(duration > 8 && duration < 12){
      Serial.printf("ONE\n");
    }
  //Serial.printf ("Duration: %i\n", duration);
  }

}
