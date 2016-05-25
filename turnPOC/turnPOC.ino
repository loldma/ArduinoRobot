const int OUT1 = 2;
const int OUT2 = 3;
const int OUT3 = 4;
const int OUT4 = 5;

const int SPEED = 80;

const int DEGREE_90_DELAY = 700;

void setup() {
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  delay(2000);
}

void loop() {
  turnLeft(90);
  stop();
  delay(1000);
  turnRight(90);
  stop();
  delay(1000);
  turnLeft(45);
  stop();
  delay(1000);
  turnRight(45);
  stop();
  delay(2000);

}

void turnRight(int degree) {
  rightForward();
  leftBackward();
  int delayDegree = countDegreeDelay(degree);
  delay(delayDegree);
}

void turnLeft(int degree) {
  rightBackward();
  leftForward();
  int delayDegree = countDegreeDelay(degree);
  delay(delayDegree);
}

/**
   Spins the right motor forward
*/
void rightForward() {
  analogWrite(OUT1, SPEED);
  analogWrite(OUT2, LOW);
}

/**
   Spins the right motor backward
*/
void rightBackward() {
  analogWrite(OUT2, SPEED);
  analogWrite(OUT1, LOW);
}

/**
   Spins the left motor forward
*/
void leftForward() {
  analogWrite(OUT3, SPEED);
  analogWrite(OUT4, LOW);
}

/**
   Spins the left motor backward
*/
void leftBackward() {
  analogWrite(OUT4, SPEED);
  analogWrite(OUT3, LOW);
}

/**
   Spins both motors forward
*/
void forward() {
  rightForward();
  leftForward();
}

/**
   Spins both motors backward
*/
void backward() {
  rightBackward();
  leftBackward();
}

/**
   Stops both motors
*/
void stop() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);

}

/**
  Calculates the time needed to turn the given degree
*/
int countDegreeDelay(int degree) {
  return (DEGREE_90_DELAY / 90 * degree);
}
