
// straw stab button
const int stabButton = A2;
int stabOut = LOW;
int count = 0;
int success = 4;
int fail = 3;

//joystick input pins
const int VRX = A0;
const int VRY = A1;
int xvalue = 0;
int yvalue = 0;
int joystickMoves = 0;
bool up = false;
bool down = false;
bool left = false;
bool right = false;
bool complete = false;

const int LED1 = 5; //left
const int LED2 = 6; //right
const int LED3 = 7; // down
const int LED4 = 8; // up

unsigned long int pre = 0;
unsigned long int post = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(VRX, INPUT);
  pinMode(stabButton, INPUT_PULLUP);
  pinMode(VRY, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(success, OUTPUT);
  pinMode(fail, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  // read analog X and Y analog values
  digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);

 
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
    if ((down==true) && (up==true) && (right==true) && (left==true)) 
      {
        // increase the number of moves made, and return success when enough rotations
        joystickMoves++;
        if (joystickMoves > 2)
        {
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
