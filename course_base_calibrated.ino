/*
Course Template from Sunfounder Documentation

https://docs.sunfounder.com/projects/3in1-kit-v2/en/latest/car_project/car_move_by_code.html

Modify to complete the courses
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

// Course Steps
// - This is where you use the car functions below to instruct your car to complete the course
//  as fast as possible
// - You may need to change your speed before each step, so keep in mind that the minimum speed
//  is 0 and the max speed is 255
void loop() {
  // Do not touch this stopMove part
  int speed = 150; // DO NOT TOUCH
  stopMove(speed); // DO NOT TOUCH
  delay(1000); // DO NOT TOUCH

  // Start making changes here:
  // - Replace any of the example instructions below
  // - Do Not replace the last stopMove part
  moveForward(speed); // Example
  delay(1000); // Example

  slowDown(speed); // Example
  delay(500); // Example

  speed = 255; // Example
  moveBackward(speed); // Example
  delay(500); // Example

  moveLeft(speed); // Example
  delay(500); // Example

  moveRight(speed); // Example
  delay(500); // Example
  
  // Do not touch this stopMove part
  speed = 150; // DO NOT TOUCH
  stopMove(speed); // DO NOT TOUCH
  delay(1000); // DO NOT TOUCH
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
