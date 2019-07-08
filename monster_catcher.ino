/*
   Monster Catcher - Colleen Carroll @colleeninboots
*/

#include <Servo.h>

const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;
const int SHUT_PIN = 7;
const int OPEN_PIN = 8;
const int TOP_SERVO_PIN = 9;
const int BOTTOM_SERVO_PIN = 10;
const int POT_PIN = A3;
Servo topServo;
Servo bottomServo;

int shut = 1;

int lastMonster = 0;
unsigned long lastTimeStampMs = 0;
unsigned long delayedShutInterval = 3000;  // the delay before snapping the trap shut after a 
                                            // monster type is chosen. 3 seconds.
void setup() {
  pinMode(OPEN_PIN, INPUT);
  pinMode(SHUT_PIN, INPUT);
  
  topServo.attach(TOP_SERVO_PIN);
  bottomServo.attach(BOTTOM_SERVO_PIN);
  
  openTrap();
  
  // Serial.begin(9600); for debugging
}

void loop() {
  int isOpenPushed = digitalRead(OPEN_PIN);
  int isShutPushed = digitalRead(SHUT_PIN);

  //buttonResponse(isOpenPushed, isShutPushed);
    
  int potValue = analogRead(POT_PIN);
  potResponse(potValue);
}

// TODO
void isShut() {
  
}

/* Responds to button states: isOpenPushed and isShutPushed. 
 * Prioritizes open if both are pushed.
 */
void buttonResponse(int isOpenPushed, int isShutPushed) {
  if (isOpenPushed && shut) { 
    openTrap();
    Serial.println("OPEN!");
  }
  else if(!isOpenPushed && isShutPushed && !shut) {  // check isOpenPushed to handle two button push
    shutTrap();
    Serial.println("SHUT!");
  }
}


void openTrap() {
  if (!shut) { // Don't do anything if servo state is already open.
    return;
  }
  Serial.println("opening");
  
  lastMonster = 0; // reset the lastTimeStampMs and lastMonster so that the trap
  lastTimeStampMs = millis();  // doesn't immediately close again if the LED is on
                              
  moveServos(bottomServo, topServo);
  shut = 0;
}

void shutTrap() {
  if (shut) { // Don't do anything if servo state is already shut.
    return;
  }
  Serial.println("closing");

  moveServos(topServo, bottomServo);
  shut = 1;
}

// if the monster type (color trimpot) stays the same for 10 seconds, shut the trap
void delayedShut(int thisMonster) {
  unsigned long thisTimeStampMs = millis();

  if(lastMonster == 0 || thisMonster != lastMonster) {
    Serial.print("lastMonster: ");
    Serial.print(lastMonster);
    Serial.print(" | thisMonster: ");
    Serial.println(thisMonster);
    lastTimeStampMs = thisTimeStampMs;
  }
  else if (thisMonster == lastMonster){
    if (thisTimeStampMs - lastTimeStampMs >= delayedShutInterval) {
      shutTrap();
    }
  }
  lastMonster = thisMonster;
}



void moveServos(Servo servoToMax, Servo servoTo0) {
  int maxAngle = 90;
  int stepSize = 10; // size of each step in degrees
  int delayTime = 5;  // delay between each step in ms
  
  for (int i = 0; i <= maxAngle; i += stepSize) { // goes from 0 degrees to maxAngle degrees
                                      // in steps of 1 degree
    servoToMax.write(i);              // tell servo to go to position in variable 'i'
    delay(delayTime);                        // waits 15ms for the servo to reach the position
  }
  for (int j = maxAngle; j >= 0; j -= stepSize) { // goes from maxAngle degrees to 0 degrees
    servoTo0.write(j);                // tell servo to go to position in variable 'j'
    delay(delayTime);                        // waits 15ms for the servo to reach the position
  }
}

void potResponse(int potValue) {
  int monsterType = map(potValue, 0, 1025, 0, 6);
//  Serial.print("potValue: ");
//  Serial.print(potValue);
//  Serial.print(" | monster: ");
//  Serial.println(monsterType);

  switch (monsterType) {
    case 0: // ALL
      setColorRGB(0, 0, 0); // White
      openTrap();
      break;
    case 1:
      setColorRGB(255, 100, 0); // Yellow
      delayedShut(monsterType);
      break;
    case 2:
      setColorRGB(0, 255, 0); // Green
      delayedShut(monsterType);
      break;
    case 3:
      setColorRGB(0, 0, 255); // Blue
      delayedShut(monsterType);
      break;
    case 4:
      setColorRGB(255, 0, 0); // Red
      delayedShut(monsterType);
      break;
    case 5:
      setColorRGB(128, 0, 100); // Purple
      delayedShut(monsterType);
      break;
    default:
      setColorRGB(0,0,0); // Black, aka Off
      openTrap();
      break;
  }
}

void setColorRGB(int red, int green, int blue) {
  analogWrite(RED_PIN, 255 - red);
  analogWrite(GREEN_PIN, 255 - green);
  analogWrite(BLUE_PIN, 255 - blue);
 }
