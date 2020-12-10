
/*
 * Project RecieverKeyOLED
 * Description:
 * Author:
 * Date:
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include <Adafruit_SSD1306.h>

#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);

const int anodePin = A5; 

//revert to here before SERVO

Servo myServo;

int servoRead;

int anodeRead; 
int triggerValue = 100;
unsigned int zeroTime = 200;
unsigned int zeroMin = 100;
unsigned int zeroMax = 300;
unsigned int oneTime = 400;
unsigned int oneMin = 320;
unsigned int oneMax = 500;
// unsigned int zeroTime = 500;
// unsigned int zeroMin = 250;
// unsigned int zeroMax = 750;
// unsigned int oneTime = 1000;
// unsigned int oneMin = 800;
// unsigned int oneMax = 1250;
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
bool hasRun = false;


void setup() {

  Serial.begin(9600);

  myServo.attach(D5);
  myServo.write(100);

  pinMode(anodePin, INPUT);

  pinMode(D7, OUTPUT); //for testing only
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  // display.setRotation(1);
  display.setTextSize(2);
  display.setTextColor(WHITE);


  delay(1000); //set up time
  Serial.printf("System Ready...");
  display.printf("SYSTEM\nREADY\n*LOCKED*");
  display.display();

}
void loop() {


  anodeRead = analogRead(anodePin);
 // Serial.printf("Anode: %i\n", anodeRead); //used for testing

  
  if (i == 5){
    displayKey();
  }

  if (i > 5){ //do not change
   i = 1; //do not change 
   hasRun = false;
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

    bitZero = array[1];
    bitOne = array[2];
    bitTwo = array[3];
    bitThree = array[4];
    bitFour = array[5];

}

void displayKey() {


  if(bitZero == 0 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 1){

    if((hasRun == false)){
    //Serial.printf("Yellow button\n");
    lockServo();
    }

    
  }
  else if(bitZero == 1 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 0){
    
    if((hasRun == false)){
    //Serial.printf("Blue button\n");
    unlockServo();

    }
  }

}

void unlockServo(){

    display.clearDisplay();
    display.setCursor(0,0);
    display.printf("CODE TAKENSYSTEM\nDISARMED");
    display.display();
    myServo.write(0);
     delay(1000);
    analogWrite(D7, 255); //for testing only
    Serial.printf("Blue Button\n");
    hasRun = true;
  
}

void lockServo(){

    display.clearDisplay();
    display.setCursor(0,0);
    display.printf("INCORRECT CODE\nSYSTEM\nLOCKED");
    display.display();
    myServo.write(100);
     delay(1000);
    analogWrite(D7, 20); //for testing only
    Serial.printf("Yellow button\n");
    hasRun = true;
}





// SYSTEM_MODE(SEMI_AUTOMATIC);

// #include <Adafruit_SSD1306.h>

// #define OLED_RESET D4

// Adafruit_SSD1306 display(OLED_RESET);

// const int anodePin = A5; 

// //revert to here before SERVO

// Servo myServo;

// int servoRead;

// int anodeRead; 
// int triggerValue = 100;
// // unsigned int zeroTime = 1000;
// // unsigned int zeroMin = 500;
// // unsigned int zeroMax = 1500;
// // unsigned int oneTime = 2000;
// // unsigned int oneMin = 1600;
// // unsigned int oneMax = 2500;
// unsigned int zeroTime = 500;
// unsigned int zeroMin = 250;
// unsigned int zeroMax = 750;
// unsigned int oneTime = 1000;
// unsigned int oneMin = 800;
// unsigned int oneMax = 1250;
// unsigned int startTime;
// unsigned int endTime;
// unsigned int duration;
// bool timerState;
// int array[6];
// int arrayMax = 5;
// int i = 0;
// int bitZero; //maybe make these bools 
// int bitOne; 
// int bitTwo;
// int bitThree;
// int bitFour;
// int n;
// bool printState;
// bool buttonState;
// bool lastButton;


// void setup() {

//   Serial.begin(9600);

//   myServo.attach(D5);

//   pinMode(anodePin, INPUT);

//   pinMode(D7, OUTPUT); //for testing only
 
//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//   display.display();
//   display.clearDisplay();
//   // display.setRotation(1);
//   display.setTextSize(2);
//   display.setTextColor(WHITE);


//   delay(1000); //set up time
//   Serial.printf("System Ready...");
//   display.printf("ALARM\nSYSTEM\nREADY");
//   display.display();

// }
// void loop() {


//   anodeRead = analogRead(anodePin);
//   //Serial.printf("Anode: %i\n", anodeRead); //used for testing
  
//   if (i == 5){
//   buttonState = true;
//     if(buttonState != lastButton){
//       if(buttonState == true){
//         printState =! printState;
//       }
//     }
//     lastButton = buttonState;
//   }
//   //Serial.printf("Button state: %i, lastButton %i, printState: %i\n", buttonState, lastButton, printState);

//   if (i > 5){ //do not change
//    i = 1; //do not change 
//   }

//   if (!timerState && anodeRead > triggerValue){ //if timer is not running and anode is triggered then run
//     startTime = millis();
//     timerState = true;
//     i++; //sets i = to 1 right away
//   }

//   if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
//     endTime = millis();
//     timerState = false;
//     duration = endTime - startTime;

//     if(duration > zeroMin && duration < zeroMax){
//       array[i] = 0;
//       Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
//     }
//     else if(duration > oneMin && duration < oneMax){
//       array[i] = 1;
//       Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
//     }
//   }

//     bitZero = array[1];
//     bitOne = array[2];
//     bitTwo = array[3];
//     bitThree = array[4];
//     bitFour = array[5];

// }

// void displayKey() {

//     if(bitZero == 0 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 1){
    
//     //Serial.printf("Yellow button\n");
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.printf("INCORRECT CODE\nSYSTEM\nLOCKED");
//     display.display();
//     unlockServo();
//     analogWrite(D7, 20); //for testing only
    
//   }
//   else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
//     //Serial.printf("Blue button\n");
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.printf("CODE TAKENSYSTEM\nDISARMED");
//     display.display();
//     lockServo();
//     analogWrite(D7, 255); //for testing only

//   }

// }





// void unlockServo(){
//   myServo.write(180);
// }

// void lockServo(){
//   myServo.write(0);
// }



//below is working***
// /*
//  * Project RecieverKeyOLED
//  * Description:
//  * Author:
//  * Date:
//  */

// SYSTEM_MODE(SEMI_AUTOMATIC);

// #include <Adafruit_SSD1306.h>

// #define OLED_RESET D4

// Adafruit_SSD1306 display(OLED_RESET);

// const int anodePin = A5; 

// //revert to here before SERVO

// Servo myServo;

// int servoRead;

// int anodeRead; 
// int triggerValue = 100;
// // unsigned int zeroTime = 1000;
// // unsigned int zeroMin = 500;
// // unsigned int zeroMax = 1500;
// // unsigned int oneTime = 2000;
// // unsigned int oneMin = 1600;
// // unsigned int oneMax = 2500;
// unsigned int zeroTime = 500;
// unsigned int zeroMin = 250;
// unsigned int zeroMax = 750;
// unsigned int oneTime = 1000;
// unsigned int oneMin = 800;
// unsigned int oneMax = 1250;
// unsigned int startTime;
// unsigned int endTime;
// unsigned int duration;
// bool timerState;
// int array[6];
// int arrayMax = 5;
// int i = 0;
// int bitZero; //maybe make these bools 
// int bitOne; 
// int bitTwo;
// int bitThree;
// int bitFour;
// int n;
// bool printState;


// void setup() {

//   Serial.begin(9600);

//   myServo.attach(D5);

//   pinMode(anodePin, INPUT);

//   pinMode(D7, OUTPUT); //for testing only
 
//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//   display.display();
//   display.clearDisplay();
//   // display.setRotation(1);
//   display.setTextSize(2);
//   display.setTextColor(WHITE);


//   delay(1000); //set up time
//   Serial.printf("System Ready...");
//   display.printf("ALARM\nSYSTEM\nREADY");
//   display.display();

// }
// void loop() {


//   anodeRead = analogRead(anodePin);
//   //Serial.printf("Anode: %i\n", anodeRead); //used for testing
  
//   if (i == 5){
//     displayKey();
//     printState = false;
//   }

//   if (i > 5){ //do not change
//    i = 1; //do not change 
//   }

//   if (!timerState && anodeRead > triggerValue){ //if timer is not running and anode is triggered then run
//     startTime = millis();
//     timerState = true;
//     i++; //sets i = to 1 right away
//   }

//   if (timerState && anodeRead < triggerValue){ // if timer is running and anode is not triggered then run
//     endTime = millis();
//     timerState = false;
//     duration = endTime - startTime;

//     if(duration > zeroMin && duration < zeroMax){
//       array[i] = 0;
//       Serial.printf("ZERO i = %i Array Value: %i\n", i, array[i]);
//     }
//     else if(duration > oneMin && duration < oneMax){
//       array[i] = 1;
//       Serial.printf("ONE  i = %i Array Value: %i\n", i, array[i]);
//     }
//   }

//     bitZero = array[1];
//     bitOne = array[2];
//     bitTwo = array[3];
//     bitThree = array[4];
//     bitFour = array[5];

// }

// void displayKey() {

//     if(bitZero == 0 && bitOne == 1 && bitTwo == 0 && bitThree == 1 && bitFour == 1){
    
//     //Serial.printf("Yellow button\n");
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.printf("INCORRECT CODE\nSYSTEM\nLOCKED");
//     display.display();
//     unlockServo();
//     analogWrite(D7, 20); //for testing only
    
//   }
//   else if(bitZero == 1 && bitOne == 0 && bitTwo == 1 && bitThree == 0 && bitFour == 0){
//     //Serial.printf("Blue button\n");
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.printf("CODE TAKENSYSTEM\nDISARMED");
//     display.display();
//     lockServo();
//     analogWrite(D7, 255); //for testing only

//   }

// }

// void unlockServo(){
//   myServo.write(180);
// }

// void lockServo(){
//   myServo.write(0);
// }