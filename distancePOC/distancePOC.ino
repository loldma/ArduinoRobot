#include <Servo.h>
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = A8;

int distances[11];
Servo servo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
}

void loop() {
  delay(1100);

  readDistances();
  printDistances();
  Serial.print(getMaxDistancePosition());
  println();

  /*for (int i = 0; i<11; i++) {
    Serial.print(i);
    println();
    if (isLeftTurnNeeded(i)) {
      Serial.print("left");
      println();
    } else {
      Serial.print("right");
      println();
    }
    Serial.print(degreeNeededToTurn(i));
    println();
    }
    delay(50000);*/
}

int checkDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 29 / 2;
  return distance;
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

boolean isLeftTurnNeeded(int pos) {
  return pos < 5;
}

int degreeNeededToTurn(int pos) {
  pos -= 5;
  return (15 * abs(pos));
}

void println(String s) {
  Serial.print("\n");
}

void printDistances() {
  for (int i = 0; i < 11; i++) {
    Serial.print(distances[i]);
    Serial.print(", ");
  }
  println();
}


