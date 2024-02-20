#include <LiquidCrystal.h>

const int powerSw = 2;
const int failLED = 3;
const int successLED = 4;
const int resetButton = 13;
//command input pins
const int scoopSwitch = 5;
const int stabButton = 6;
const int cardSwipe = A2;
//joystick input pins
const int VRX = A0;
const int VRY = A1;
//speaker output pin
const int speaker = A3;
//LCD output pins
const int RS = 7;
const int EN = 8;
const int D4 = 9;
const int D5 = 10;
const int D6 = 11;
const int D7 = 12;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//changing variables
int score = 0;
int roundCounter = 0;
unsigned long timer = 1000;
int commandArr[4] = {0, 1, 2, 3};
int command = 0;
int stabOut = HIGH;
int scoopOut = HIGH;
int swipeOut = HIGH;
int shakeOut = HIGH;
bool stabSuccess = false;
bool scoopSuccess = false;
bool swipeSuccess = false;
bool shakeSuccess = false;
bool gameOver = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(powerSw, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  pinMode(scoopSwitch, INPUT_PULLUP);
  pinMode(stabButton, INPUT_PULLUP);
  pinMode(cardSwipe, INPUT_PULLUP);
  pinMode(VRX, INPUT_PULLUP);
  pinMode(VRY, INPUT_PULLUP);
  pinMode(failLED, OUTPUT);
  pinMode(successLED, OUTPUT);
  pinMode(speaker, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(resetButton) == LOW) {
    reset();
  }
  if (gameOver) {
    gameOverFxn();
  }
  //go through commands
  else {
    //randomly access command array to pick command to be done
    command = commandArr[int(floor(random(0, 4)))];
    delay(timer);
    //activate command based on random number
    switch (command) {

      //stab command
      case 0:
        stabOut = digitalRead(stabButton);
        if (stabOut == LOW) stabSuccess == true;
        else if (stabOut == HIGH) stabSuccess == false;
        if (stabSuccess) {
          successFxn();
        }
        else {
          failFxn();
        }
      break;

      //shake command
      case 1:
        //read joystick input for success or fail
        if (shakeSuccess) {
          successFxn();
        }
        else {
          failFxn();
        }
      break;

      //swipe command
      case 2:
        swipeOut = analogRead(cardSwipe);
        if (swipeOut >= 500) swipeSuccess = true;
        else if (swipeOut < 500) swipeSuccess = false;
        if (swipeSuccess) {
          successFxn();
        }
        else {
          failFxn();
        }
      break;

      //scoop command
      case 3:
        scoopOut = digitalRead(scoopSwitch);
        if (scoopOut == LOW) scoopSuccess = true;
        else if (scoopOut == HIGH) scoopSuccess = false;
        if (scoopSuccess) {
          successFxn();
        }
        else {
          failFxn();
        }
      break;
    }
  }
}

void reset() {
  //resets game
  score = 0;
  timer = 1000;
  lcd.clear();
  delay(1000);
}

void successFxn() {
  score++;
  roundCounter++;
  digitalWrite(successLED, HIGH);
  delay(500);
  digitalWrite(successLED, LOW);
}

void failFxn() {
  digitalWrite(failLED, HIGH);
  delay(500);
  digitalWrite(failLED, LOW);
  gameOver = true;
}

void gameOverFxn() {
  lcd.print(char(score));
}