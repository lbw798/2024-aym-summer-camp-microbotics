/*
Move Fast Template from Sunfounder Documentation

https://docs.sunfounder.com/projects/3in1-kit-v2/en/latest/car_project/car_move_by_code.html

Challenge: complete numbered tasks in file
*/

// 1. Assign the pins where you will be plugging in the motor control wires
// - hint: look at Arduino wiring
const int A_1B = BLANK; // analog (marked with ~) pin number where wire is connected
const int A_1A = BLANK; // analog (marked with ~) pin number where wire is connected
const int B_1B = BLANK; // analog (marked with ~) pin number where wire is connected
const int B_1A = BLANK; // analog (marked with ~) pin number where wire is connected

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
  // 3. Add code to make your car return to starting position
}

// Move Functions
// 2. Add moveBackward function
// - hint: look at the previous move function you copied
void moveForward(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, speed);
  analogWrite(B_1A, 0);
}

// 4. Check answers with your continent's TA
