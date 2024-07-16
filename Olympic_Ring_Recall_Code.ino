/*
   Ron D Bentley, Stafford, UK
   Feb 2021

   Buttons  & Lights Game
   '''''''''''''''''''''

   This example and code is in  the public domain and may be used without restriction and
   without warranty.

   Basic game of Buttons & Lights
   Game flow:
   - game starts by blinking  all 4 leds 4 times
   - a sequence of 4, 5 or 6 leds are then illuminated, in  turn, at the end
     of which a 20 second timer then starts within which the  sequence must
     be entered on the button switches, each button switch one  coresponding to an
     associated led
   - if correct sequence is entered  then the green led will flash 5 times
   - if the incorrect sequence is entered  them the red led will flash 5 times
   - if the sequence is not fully entered  within the given time then the
     blue led will flash 5 times and the game  reset for the next round.

   Configurability:
   1. sequence size for  illuminated leds - the number of guesess is defined by
      the sequence size  definition ('#define max_sequence'). Change this as
      required, but should  be > 4 for a reasonable game.
   2. game time - the duration for entering the  guess sequence is controlled
      by the variable 'int guess_duration'. This  should be set with the time in
      milliseconds given for the guess period.
*/

#define  num_switches          4   // number of button switches connected
struct switch_control  {// digital input pin control data structure
  int switch_pin;                 //  digital button switch input pin,
  bool switch_pending;            // records  if switch in transition or not,
  long unsigned int elapse_timer; // records  debounce timer count when associated switch is in transition
} switches[num_switches]  = {
  8,  false, 0,
  9,  false, 0,
  10, false, 0,
  11, false, 0
};

#define  success            true    // used for verifying guesses sequence
#define switched           true    // signifies switch has been pressed
#define debounce             10    // number of milliseconds to wait for switch to settle once pressed

int  leds[num_switches] = {// analogue outputs, one for each digital input/switch
  A0,
  A1,
  A2,
  A3
};

#define red_led   A0  // failed guess  indicator
#define green_led A2  // successful guess indicator
#define blue_led  A3  // timed out indicator, before guess fully made

#define max_sequence                 6   // must be >= 4 for a reasonable game, change if more wanted
int  sequence[max_sequence + 1];          // records sequence to guess.[0] will hold  number of entries in array

#define number_of_guesses max_sequence
int  guesses[number_of_guesses + 1];      // records player's guesses. [0] will hold  number of entries in array

long unsigned int start_time =      0;   // used  to time start of a game
int guess_duration           =  10000;   // duration  time given to a play game, in millisecs

void setup() {
  int sw;
  //  initialise digital input switch pins and their associated LEDs
  for (sw = 0;  sw < num_switches; sw++) {
    pinMode(switches[sw].switch_pin, INPUT_PULLUP);  // pin willbe HIGH unless switched
    pinMode(leds[sw], OUTPUT);
  }
  randomSeed(analogRead(A4)); // A4 not used in this sketch as a connected output
  reset_game();  // set up first game
}

void loop() {
  if (millis()  - start_time > guess_duration) {
    // play time out
    flash_led(blue_led,  5);  // flash failure
    delay(2000);
    reset_game();
  } else {
    if (guesses[0] < sequence[0]) {
      // poll switches again for a selection
      for (int sw = 0; sw < num_switches; sw++) {
        if (read_switch(sw)  == switched) {
          // this button is pressed so record it - add to guess  list
          guesses[0]++;
          guesses[guesses[0]] = sw;  // record  this switch's position in control struct(ure)
        }
      }
    } else  {
      //  all guesses made within the play time - check if correct
      if  (check_sequence() == success) {
        // guessed correct
        flash_led(green_led,  5);  // flash success
      } else {
        // guess incorrect
        flash_led(red_led,  5);    // flash failure
      }
      delay(2000);
      reset_game();
    }
  }
}

//
// game reset, clear down and generate a new sequence
//
void  reset_game() {
  int i, num_in_sequence;
  guesses[0] = 0;  // clear down  previous guesses
  // set up a new sequence for next game
  num_in_sequence  = random(4, max_sequence + 1); // pick new sequence length, at least 4 in sequence
  for (i = 1; i <= num_in_sequence; i++) {
    sequence[i] = random(0, num_switches);       // index to switch pin/led array
  }
  sequence[0] = num_in_sequence;
  flash_all_leds(4);
  delay(2000);
  play_sequence();
  start_time = millis();  // set guess timer start time
}

//
// flash leds in the order defined  by the sequence list
// 
void play_sequence() {
  int i;
  for (i =  1; i <= sequence[0]; i++) {
    analogWrite(leds[sequence[i]], 255);
    delay(1000);
    analogWrite(leds[sequence[i]], 0);
    delay(1000);
  }
}

//
//  check off guessed button presses against the sequence
//
bool check_sequence()  {
  int i;
  for (i = 1; i <= guesses[0]; i++) {
    if (guesses[i] !=  sequence[i]) {
      return !success;
    }
  }
  return success;
}

//
//  flash given led the given number of times
//
void flash_led(int led, int num)  {
  for (int i = 1; i <= num; i++) {
    analogWrite(led, 255);
    delay(250);
    analogWrite(led, 0);
    delay(250);
  }
}

//
// flash all  leds the given number of times to signify game starting
//
void flash_all_leds(int  n) {
  int cycle, led, level;
  n = 2 * n; // because 1 cycle is on then off,  hence a x2 factor
  level = 0;
  for (cycle = 1; cycle <= n; cycle++) {
    level = 255 - level;
    for (led = 0; led < num_switches; led++) {
      analogWrite(leds[led],  level);
    }
    delay(250);
  }
}

//
// read the switch  connected to the given pin
// note that this function works in a nonexclusive  way
// and incorporates debounce code
//
bool read_switch(int sw) {
  int             switch_pin_reading;
  switch_pin_reading = digitalRead(switches[sw].switch_pin);
  if (switch_pin_reading == LOW) {
    // switch is pressed, so start/restart  debounce process
    switches[sw].switch_pending = true;
    switches[sw].elapse_timer  = millis();    // start elapse timing
    return !switched;           // now  waiting for debounce to conclude
  }
  if (switches[sw].switch_pending &&  switch_pin_reading == HIGH) {
    // switch was pressed, now released, so check  if debounce time elapsed
    if (millis() - switches[sw].elapse_timer > debounce)  {
      // dounce time elapsed, so switch press cycle complete
      switches[sw].switch_pending  = false;
      return switched;
    }
  }
  return !switched;
}
