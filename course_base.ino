/*
Move Fast Template from Sunfounder Documentation

https://docs.sunfounder.com/projects/3in1-kit-v2/en/latest/car_project/car_move_by_code.html

Challenge: complete numbered tasks in file
*/

// Pin Assignments
const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

// Pin Signal Mode
void setup() {
  pinMode(A_1B, OUTPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
}

// Course Steps
// - This is where you use the car functions below to instruct your car to complete the course
//  as fast as possible
// - You may need to change your speed before each step, so keep in mind that the minimum speed
//  is 0 and the max speed is 255
void loop() {
  int speed = 150;
  stopMove(speed);
  delay(1000);

  speed = 155; //
  stopMove(speed);
  delay(1000);
}

// Car Functions
void moveForward(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, speed);
  analogWrite(B_1A, 0);
}

void slowDown(int speed) {
  for(int i=speed;i>=0;i-=5){
    moveForward(i);
    delay(10);
  }
}

void moveBackward(int speed) {
  analogWrite(A_1B, speed);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, speed);
}

void moveLeft(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);
}

void moveRight(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, speed);
  analogWrite(B_1A, 0);
}

void turnRight(int speed) {
  digitalWrite(A_1B, speed);
  digitalWrite(A_1A, 0);
  digitalWrite(B_1B, speed);
  digitalWrite(B_1A, 0);
}

void turnLeft(int speed) {
  digitalWrite(A_1B, 0);
  digitalWrite(A_1A, speed);
  digitalWrite(B_1B, 0);
  digitalWrite(B_1A, speed);
}

void stopMove(int speed) {
  digitalWrite(A_1B, 0);
  digitalWrite(A_1A, 0);
  digitalWrite(B_1B, 0);
  digitalWrite(B_1A, 0);
}
