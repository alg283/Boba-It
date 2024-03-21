#include <LiquidCrystal.h>

const int failLED = 3;
const int successLED = 4;
const int resetButton = 2; // needs to be tested later
const int buzzer = A3;

//command input pins
const int scoopSwitch = A4;
const int stabButton = A2; // actual pin input
const int cardSwipe = 44;

//joystick input pins and joystick specific moves
const int VRX = A0;
const int VRY = A1;
int xvalue = 0;
int yvalue = 0;
int joystickMoves = 0;
bool up,down,left,right = false;
bool butt = false;

const int b4 = 10; //16
const int b3 = 9;
const int b2 = 0;
const int b1 = 1;
const int b0 = A5;


//changing variables
int score = 0;
unsigned long timer = 10000;
unsigned long preCommand = 0;
unsigned long postCommand = 0;
int commandArr[4] = {0, 1, 2, 3};
int command = 0;
bool stabOut = false;
bool scoopOut = false;
int swipeOut = HIGH;
int shakeOut = HIGH;

bool gameOver = false;
bool swipeSuccess;

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
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(scoopSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(stabButton, INPUT_PULLUP); // verified
  pinMode(cardSwipe, INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(failLED, OUTPUT);
  pinMode(successLED, OUTPUT);
  pinMode(speaker, OUTPUT);

  pinMode(b4, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b0, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(resetButton) == HIGH) 
  {
    reset();
  }
  //go through commands
  else 
  {

    //randomly access command array to pick command to be done
    preCommand = millis();
    //command = commandArr[int(floor(random(0, 3)))];
    command = 0;
 // Serial.println(command); // will become speaker output eventually

    //activate command based on random number
      switch (command) {

        //stab command
        case 0:
          stabOut = stabSuccess(timer);
          if (stabOut) 
          {
            successFxn();
          }
          else 
          {
            gameOverFxn();
          }
          break;
        //shake command
        case 1:
          //read joystick input for success or fail
          butt = shakeSuccess(timer);
          if (butt) 
          { // && timer did not run out
            successFxn();
          }
          else 
          {
            gameOverFxn();
            //for testing purposes
            //roundSuccess = successFxn();
          }
          break;

        case 2:
          scoopOut = scoopSuccess(timer);
          if (scoopOut) 
            successFxn();
          else
            gameOverFxn();
          break;

  }
    //time hath run out
  
  }
}


void reset() {
  //resets game
  digitalWrite(failLED,LOW);
  digitalWrite(successLED,LOW);
  score = 0;
  timer = 8000;
  //lcd.clear();
  delay(1000);
}

void successFxn() {
  score++;
  timerDec();
  digitalWrite(successLED, HIGH);
  delay(500);
  digitalWrite(successLED, LOW);
}


void gameOverFxn() {
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(failLED,HIGH);
  tone(buzzer,500);
  //lcd.print(char(score));
  while (digitalRead(resetButton) == LOW) {continue;}
  gameOver = false;
  //digitalWrite(failLED,LOW);
}


bool shakeSuccess(unsigned long timer)
{
  unsigned long immediateStartTime = millis();
  digitalWrite(LED4,HIGH);
  while (millis() - immediateStartTime < timer) // could be replaced with while(timer has not run out)
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
          digitalWrite(LED4,LOW);
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
      else if (digitalRead(stabButton) == HIGH)
        gameOverFxn();
      else if (digitalRead(scoopSwitch)==HIGH)
        gameOverFxn();
  }
  return false;
}

// this led is broken
bool stabSuccess(unsigned long timer)
{
  unsigned long immediateStartTime = millis();
  digitalWrite(LED1,HIGH);
  while(millis() - immediateStartTime < timer)
  {
    xvalue = analogRead(VRX);
    yvalue = analogRead(VRY);
    if (xvalue<400 || xvalue>800)
      {
        if (yvalue>800 || yvalue<400)
          gameOverFxn();
      }

    if (digitalRead(stabButton) == HIGH) 
      {
      digitalWrite(LED1,LOW);
      return true;
      }
    else if (digitalRead(scoopSwitch)==HIGH)
      gameOverFxn();
    
  }
  digitalWrite(LED1,LOW);
  return false;
}

// this led is broken
bool scoopSuccess(unsigned long timer)
{
  unsigned long immediateStartTime = millis();
  digitalWrite(LED3,HIGH);
  while (millis() - immediateStartTime < timer) // could be replaced with while(timer has not run out)
  {
    xvalue = analogRead(VRX);
    yvalue = analogRead(VRY);
    if (xvalue<400 || xvalue>800)
      {
        if (yvalue>800 || yvalue<400)
          gameOverFxn();
      }
      
    if (digitalRead(scoopSwitch) == LOW)
    {
      digitalWrite(LED3,LOW);
      return true;
    }
    else if (digitalRead(stabButton)==HIGH)
      gameOverFxn();
  }
  digitalWrite(LED3,LOW);
  return false;
}

void timerDec() {
  if (timer != 1000)
  {
    if (score%3 == 0) {
      timer -= 500;
  }
  }
}