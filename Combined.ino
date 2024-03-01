
// straw stab button
const int stabButton = A2;

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


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(VRX, INPUT);
  pinMode(stabButton, INPUT_PULLUP);
  pinMode(VRY, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  // read analog X and Y analog values
  complete = shakeSucces();
  if (complete==true)
    digitalWrite(LED4,HIGH);
  else
    digitalWrite(LED4,LOW);

  if (digitalRead(stabButton)==HIGH)
    {
      digitalWrite(LED1,HIGH);
    }
  else
    {
      digitalWrite(LED1,LOW);
    }
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
