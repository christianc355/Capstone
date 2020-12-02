/*
 * Project LaserTest
 * Description: LiFi Emitter
 * Author: Christian Chavez
 * Date: 11-23-2020
 */


SYSTEM_MODE(SEMI_AUTOMATIC);

#include <OneButton.h>
#include <Adafruit_BME280.h>


const int laserPin = A5;
const int buttonPin = D5;
const int extraButtonPin = D6;

OneButton button1(buttonPin, false, false);
OneButton button2(extraButtonPin, false, false);
Adafruit_BME280 bme;


unsigned int zeroTime = 1000;
unsigned int oneTime = 2000;
unsigned int offDelay = 500;
unsigned int zeroCurrentTime;
unsigned int zeroLastTime;
unsigned int oneCurrentTime;
unsigned int oneLastTime;

bool buttonState;
bool extraButtonState;

String temp;
char temp_array[5];
byte data[8];
int i;
int u;
int n;

void setup() {

  Serial.begin(9600);

  bme.begin(0x76);

  pinMode(laserPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(extraButtonPin, INPUT_PULLDOWN);
  pinMode(A1, OUTPUT); //used for testing 
  pinMode(D7, OUTPUT); //used for testing
  
  button1.attachClick(click1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.setClickTicks(250);

  button2.attachClick(click2);
  button2.setClickTicks(250);

}

void loop() {

  temp = String(bme.readTemperature());

  temp.toCharArray(temp_array, 5);

  for(i = 0; i < 8; i++){
    data[i] = temp_array[n] >> i && 0x01;
  }
  n++;
  Serial.printf("\ntemp_array: %s data: %i i: %i n: %i\n", temp_array, data, i, n);
  sendAscii(data);
}

void sendAscii(byte send_array[8]){
  for(i = 0; i < 8; i++){ 
      // send_array[i] = 0 == 1;

      if(send_array[i] == 0){ //laser 
      beamZero(); 
      Serial.printf("Zero");
      }
      else if(send_array[i] == 1){
      beamOne();
      Serial.printf("One");
      }
  }
}
  


void click1(){

  buttonState = !buttonState;

}

void click2(){

  extraButtonState = !extraButtonState;

}

void longPressStart1() {

  Serial.println("Button 1 longPress start");
  analogWrite(D7, 200);
  Serial.printf("Temperature: %f\n", temp);
  

} 

void longPressStop1() {

  Serial.println("Button 1 longPress stop");
  analogWrite(D7, 0);

}

void beamZero() {

  // Serial.printf("Array value is ZERO\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ZERO\n");
  delay(zeroTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);

}

void beamOne() {

  //Serial.printf("Array value is ONE\n");
  digitalWrite(laserPin, HIGH);
  //Serial.printf("ONE\n");
  delay(oneTime);
  digitalWrite(laserPin, LOW);
  delay(offDelay);

}