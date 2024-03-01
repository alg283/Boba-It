#include <LiquidCrystal.h>

const int failLED = 3;
const int successLED = 4;
const int resetButton = 2; // needs to be tested later

//command input pins
const int scoopSwitch = 5;
const int stabButton = A2; // actual pin input
const int cardSwipe = 5;

//joystick input pins and joystick specific moves
const int VRX = A0;
const int VRY = A1;
int xvalue = 0;
int yvalue = 0;
int joystickMoves = 0;
bool up,down,left,right = false;

//speaker output pin 
// pin 26
const int speaker = A3;

//LCD output pins
// ignore until LCD can be configured correctly
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
unsigned long timer = 5000;
unsigned long preCommand = 0;
unsigned long postCommand = 0;
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
bool roundSuccess = false;
bool gameOver = false;

// these are LEDs used to test cases and will be deleted
// after each component has been tested and verified
// will be used for cases until speaker is implemented
const int LED1 = 5; //left
const int LED2 = 6; //right
const int LED3 = 7; // down
const int LED4 = 8; // up

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(reset, INPUT_PULLUP);
  pinMode(scoopSwitch, INPUT_PULLUP);
  pinMode(stabButton, INPUT_PULLUP); // verified
  pinMode(cardSwipe, INPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
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
    preCommand = millis();
    command = commandArr[int(floor(random(0, 4)))];
    Serial.println(command); // will become speaker output eventually

    //activate command based on random number
    while (postCommand - preCommand <= timer) {
      if (roundSuccess = true) break;
      switch (command) {

        //stab command
        case 0:
          digitalWrite(LED1, HIGH);
          stabOut = digitalRead(stabButton);
          if (stabOut == HIGH) stabSuccess == true;
          else if (stabOut == LOW) stabSuccess == false;
          if (stabSuccess) {
            digitalWrite(LED1,LOW);
            roundSuccess = successFxn();
            continue;
            }
          else {
            roundSuccess = failFxn();
            }
        break;

        //shake command
        case 1:
          digitalWrite(LED2, HIGH);
          //read joystick input for success or fail
          if (shakeSuccess) { // && timer did not run out
            digitalWrite(LED2,LOW);
            roundSuccess = successFxn();
            continue;
          }
          else {
            //failFxn();
            //for testing purposes
            roundSuccess = successFxn();
          }
        break;

        //swipe command
        case 2:
          digitalWrite(LED3,HIGH);
          swipeOut = analogRead(cardSwipe);
          if (swipeOut >= 500) swipeSuccess = true;
          else if (swipeOut < 500) swipeSuccess = false;
          if (swipeSuccess) {
            digitalWrite(LED3,LOW);
            roundSuccess = successFxn();
            continue;
          }
          else {
            roundSuccess = failFxn();
          }
        break;

        //scoop command
        case 3:
          digitalWrite(LED4, HIGH);
          scoopOut = digitalRead(scoopSwitch);
          if (scoopOut == LOW) 
            scoopSuccess = true;
            
          else if (scoopOut == HIGH) 
            scoopSuccess = false;

          if (scoopSuccess) {
            digitalWrite(LED4,LOW);
            roundSuccess = successFxn();
            continue;
          }
          else {
            roundSuccess = failFxn();
          }
        break;
      }
    }

    //time hath run out
    if (roundSuccess == false) gameOver = true;
  }
}

void reset() {
  //resets game
  score = 0;
  timer = 5000;
  lcd.clear();
  delay(1000);
}

bool successFxn() {
  score++;
  roundCounter++;
  postCommand = millis();
  timerDec();
  digitalWrite(successLED, HIGH);
  delay(500);
  digitalWrite(successLED, LOW);
  return true;
}

bool failFxn() {
  digitalWrite(failLED, HIGH);
  delay(500);
  digitalWrite(failLED, LOW);
  gameOver = true;
  return false;
}

void gameOverFxn() {
  lcd.print(char(score));
  while (resetButton == HIGH) {}
  gameOver = false;
}

bool shakeSucces()
{
  while (true) // could be replaced with while(timer has not run out)
  {
    xvalue = analogRead(VRX);
    yvalue = analogRead(VRY);

  // if the joystick goes left
  if (xvalue < 400)
    {
      left = true;
    }
  if (xvalue > 800) // goes right
    {
      right = true;
    }
  if (yvalue > 800) // goes up
    {
      up = true;
    }
  if (yvalue < 400) // goes down
    {
      down = true;
    }

    // if the first rotation of the joystick is done
    if (down==true && up==true && right==true && left==true) 
      {
        // increase the number of moves made, and return success when enough rotations
        joystickMoves++;
        if (joystickMoves > 2)
        {
          // reset all determinations and return true
          up = false;
          down = false;
          left = false;
          right = false;
          joystickMoves = 0;
          return true;
        }
        else // restart the moves for another rotation
        {
          up = false;
          down = false;
          left = false;
          right = false;
        }
      }
  }
  return false;
}

void timerDec() {
  if (score%10 == 0) {
    timer -= 500;
  }
}