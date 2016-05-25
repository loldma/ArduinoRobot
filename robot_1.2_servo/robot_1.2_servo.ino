#include <Servo.h>

const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int SERVO_PIN = A8;
const int OUT1 = 2;
const int OUT2 = 3;
const int OUT3 = 4;
const int OUT4 = 5;

const int SPEED = 80;

const int DEGREE_90_DELAY = 700;
const int MIN_DISTANCE_LIMIT = 10;
const int MAX_DISTANCE_LIMIT = 30;

int distances[11];
int obstaleDistanceCounter = 0;
int distance = 0;

Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  delay(2000);
}

void loop()
{
  distance = checkDistance();
  if ( distance < 30) {
    obstaleDistanceCounter++;
  } else {
    obstaleDistanceCounter = 0;
  }
  if (obstaleDistanceCounter > 2) {
    obstaleDistanceCounter = 0;
    stop();
    readDistances();
    int maxPosition = getMaxDistancePosition();
    if (isRunAwayNeeded(maxPosition)) {
      turnAround();
    } else {
      int turnDegree = degreeNeededToTurn(maxPosition);
      if (turnDegree != 0 && isLeftTurnNeeded(maxPosition)) {
        turnLeft(turnDegree);
      } else {
        turnRight(turnDegree);
      }
    }
  }
  forward();
  delay(100);
}

/**
   Turns the servo from 15° to 165° in 15° steps and reads the
   distances in the given directions
*/
void readDistances() {
  int currentDistance;
  for (int i = 0; i < 11; i++) {
    int position = 180 - (i + 1) * 15;
    servo.write(position);
    delay(150);
    currentDistance = checkDistance();
    distances[i] = currentDistance;
  }
  servo.write(90);
  delay(100);
}

/**
   Helper method to get the distance data from the sensor and
   convert it to actual distance value
*/
int checkDistance() {
  long duration, calculatedDistance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  calculatedDistance = (duration / 2) / 29.1;
  //  Serial.print(calculatedDistance);
  //  Serial.print("\n");
  return calculatedDistance;
}

/**
   Searches the max value in the distances array, and gives
   back the position of the greatest one.
*/
int getMaxDistancePosition() {
  int max = 0;
  for (int i = 1; i < 11; i++) {
    if (distances[i] > distances[max]) {
      max = i;
    }
  }
  return max;
}

boolean isRunAwayNeeded(int pos) {
  return distances[pos] < 50;
}

boolean isLeftTurnNeeded(int pos) {
  return pos < 5;
}

int degreeNeededToTurn(int pos) {
  pos -= 5;
  return (15 * abs(pos));
}

/**
   Sets the motor directions to turn the tank right.
   Counts the time needed to turn the given degree
*/
void turnRight(int degree) {
  rightForward();
  leftBackward();
  int delayDegree = countDegreeDelay(degree);
  delay(delayDegree);
}

/**
   Sets the motor directions to turn the tank left.
   Counts the time needed to turn the given degree
*/
void turnLeft(int degree) {
  rightBackward();
  leftForward();
  int delayDegree = countDegreeDelay(degree);
  delay(delayDegree);
}

/**
   Goes backward for half second and turns around
*/
void turnAround() {
  backward();
  delay(500);
  turnRight(180);
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
