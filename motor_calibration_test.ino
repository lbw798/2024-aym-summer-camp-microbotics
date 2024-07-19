/*
Motor Calibration Test

https://docs.sunfounder.com/projects/3in1-kit-v2/en/latest/car_project/car_speed_calibration.html

Modify lines 29 and 30 to calibrate the motors
*/

// Import offset file
#include <EEPROM.h>

// Pin Assignments
const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

// Instantiate offset percentages (0.0 = 0% to 1.0 = 100% of motor power)
float leftOffset = 1.0;
float rightOffset = 1.0;

// Pin Signal Mode
void setup() {
  pinMode(A_1B, OUTPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  // Set percentages with EEPROM.write(motor_number, percentage_of_power)
  EEPROM.write(0, 100); //write the offset to the left motor (this is where you change the percentages: 0 - 100)
  EEPROM.write(1, 85); //write the offset to the right motor (this is where you change the percentages: 0 - 100)
  leftOffset = EEPROM.read(0) * 0.01; //read the offset
  rightOffset = EEPROM.read(1) * 0.01;//read the offset
}

// Calibration Test: drives car forward then back
// - run and modify the percentages above until car remains in
//  as straight of a line as you can get it
// - DO NOT modify
void loop() {
  int speed = 255;
  stopMove(speed);
  delay(1000);

  moveForward(speed);
  delay(4000);
  
  stopMove(speed);
  delay(2000);
}

// Car Functions
void moveForward(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, int(speed*rightOffset));
  analogWrite(B_1B, int(speed*leftOffset));
  analogWrite(B_1A, 0);
}

// Do not touch below this part unless you know what you are doing
void slowDown(int speed) {
  for(int i=speed;i>=0;i-=5){
    moveForward(i);
    delay(10);
  }
}

void moveBackward(int speed) {
  analogWrite(A_1B, int(speed*rightOffset));
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, int(speed*leftOffset));
}

void moveLeft(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, int(speed*rightOffset));
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);
}

void moveRight(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, int(speed*leftOffset));
  analogWrite(B_1A, 0);
}

void turnRight(int speed) {
  digitalWrite(A_1B, int(speed*rightOffset));
  digitalWrite(A_1A, 0);
  digitalWrite(B_1B, int(speed*leftOffset));
  digitalWrite(B_1A, 0);
}

void turnLeft(int speed) {
  digitalWrite(A_1B, 0);
  digitalWrite(A_1A, int(speed*rightOffset));
  digitalWrite(B_1B, 0);
  digitalWrite(B_1A, int(speed*leftOffset));
}

void stopMove(int speed) {
  digitalWrite(A_1B, 0);
  digitalWrite(A_1A, 0);
  digitalWrite(B_1B, 0);
  digitalWrite(B_1A, 0);
}
