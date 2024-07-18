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

// Move Sequence
void loop() {
  for(int i=0;i<=255;i+=5){
    moveForward(i);
    delay(500);
  }
  for(int i=255;i>=0;i-=5){
    moveForward(i);
    delay(500);
  }
  for(int i=0;i<=255;i+=5){
    moveBackward(i);
    delay(500);
  }
  for(int i=255;i>=0;i-=5){
    moveBackward(i);
    delay(500);
  }
}

// Move Functions
void moveForward(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, speed);
  analogWrite(B_1A, 0);
}

void moveBackward(int speed) {
  analogWrite(A_1B, speed);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, speed);
}
