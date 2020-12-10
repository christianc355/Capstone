/*
 * Project LaserTest
 * Description: LiFi Emitter
 * Author: Christian Chavez
 * Date: 11-23-2020
 */


SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#include <OneButton.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);


const int laserPin = A5;
const int buttonPin = D5;
const int extraButtonPin = D6;

OneButton button1(buttonPin, false, false);
OneButton button2(extraButtonPin, false, false);
Adafruit_BME280 bme;


// unsigned int zeroTime = 15;
// unsigned int oneTime = 40;
// unsigned int offDelay = 10;
unsigned int zeroTime = 20; //below for OLED
unsigned int oneTime = 40;
unsigned int offDelay = 150;
unsigned int zeroCurrentTime;
unsigned int zeroLastTime;
unsigned int oneCurrentTime;
unsigned int oneLastTime;

bool buttonState;
bool extraButtonState;

String temp;
char temp_array[6];
byte data[8];
int i;
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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.clearDisplay();
  // display.setRotation(1);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  delay(1000);
  display.printf("SYSTEM\nREADY...\n");
  display.display();
  Serial.printf("System Ready...\n");
  delay(3000);


}

void loop() {

  temp = String(bme.readTemperature());
  float realTemp = bme.readTemperature();
  display.clearDisplay();
  display.setCursor(0,0);
  display.display();
  display.printf("SENDING\nDATA:\n%.2f%cC",realTemp, char(247));
  display.display();

  temp.toCharArray(temp_array, 7);
  Serial.printf("Temperature: %.2f\n", realTemp);
  for(n = 0; n < 5; n++){
    for(i = 0; i < 8; i++){
      data[i] = temp_array[n] >> i & 0x01;
      Serial.printf("temp_array: %x data: %i i: %i n: %i\n", temp_array[n], data[i], i, n);
      delay(10);
    }
    sendAscii(data);
  }
  sendReturn();
}

void sendAscii(byte send_array[8]){
  for(i = 0; i < 8; i++){ 

      if(send_array[i] == 0){ //laser 
      beamZero(); 
      //Serial.printf("Zero ");
      Serial.printf("0");
      }
      else if(send_array[i] == 1){
      beamOne();
      //Serial.printf("One ");
      Serial.printf("1");
      }
  }
}

void sendReturn(){
  //00001101 \n
  beamZero();
  beamZero();
  beamZero();
  beamZero();
  beamOne();
  beamOne();
  beamZero();
  beamOne();

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