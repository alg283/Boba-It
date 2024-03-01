const int counter = A2;
const int countLED = 5;
const int success = 4;
const int fail = 3;
int count = 0;
int timer = 5000;
unsigned long preCommand = 0;
unsigned long postCommand = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(counter, INPUT);
  pinMode(countLED, OUTPUT);
  pinMode(success, OUTPUT);
  pinMode(fail, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  preCommand = millis();
  digitalWrite(success, HIGH);
  digitalWrite(fail, LOW);

  if(analogRead(counter) >= 400) {
    count++;
    digitalWrite(countLED, HIGH);
    delay(500);
    digitalWrite(countLED, LOW);
  }

  if(count%10 == 0) {
    timer -= 500;
  }

  postCommand = millis();

  while (postCommand - preCommand < timer) {}
  digitalWrite(fail, HIGH);
  digitalWrite(success, LOW);

}
