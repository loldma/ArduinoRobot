
const int SIGNAL_RIGHT_PIN = 1;
const int SIGNAL_LEFT_PIN = 0;

const int OUT1 = 9;
const int OUT2 = 6;
const int OUT3 = 5;
const int OUT4 = 3;

void setup() {
  pinMode(SIGNAL_RIGHT_PIN, INPUT);
  pinMode(SIGNAL_LEFT_PIN, INPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  delay(2000);
}

void loop()
{
  long signalRight = pulseIn(SIGNAL_RIGHT_PIN, HIGH);
  long signalLeft = pulseIn(SIGNAL_LEFT_PIN, HIGH);

  int lead1 = calculateLeadPin1(signalRight);
  int lead2 = calculateLeadPin2(signalRight);

  setRightMotor(lead1, lead2);

  lead1 = calculateLeadPin1(signalLeft);
  lead2 = calculateLeadPin2(signalLeft);

  setLeftMotor(lead1, lead2);

  delay(100);
}

/////////////////////////////////////////////////////////////////
//-------------------------SIGNAL PROCESSING-------------------//
/////////////////////////////////////////////////////////////////

/**
   Calculates the motor controlling signals first lead value
   based on the signalValue
*/
int calculateLeadPin1(long signalValue) {
  float sv = signalValue;
  if (signalValue > 1450) {
    return 0;
  } else {
    int ov = (int)((sv - 1000) / 450.0 * 255.0);
    return 255 - ov;
  }
}

/**
   Calculates the motor controlling signals second lead value
   based on the signalValue
*/
int calculateLeadPin2(long signalValue) {
  float sv = signalValue;
  if (signalValue < 1550) {
    return 0;
  } else {
    return (int)((sv - 1550) / 450.0 * 255.0);
  }
}

/////////////////////////////////////////////////////////////////
//----------------------------MOTOR CONTROLL-------------------//
/////////////////////////////////////////////////////////////////

/**
   Based on the lead values sets the left motors output PWM
*/
void setLeftMotor(int lead1, int lead2) {
  if (lead1 <= 0) {
    analogWrite(OUT1, LOW);
  } else {
    analogWrite(OUT1, lead1);
  }

  if (lead2 <= 0) {
    analogWrite(OUT2, LOW);
  } else {
    analogWrite(OUT2, lead2);
  }
}

/**
   Based on the lead values sets the right motors output PWM
*/
void setRightMotor(int lead1, int lead2) {
  if (lead1 == 0) {
    analogWrite(OUT3, LOW);
  } else {
    analogWrite(OUT3, lead1);
  }

  if (lead2 == 0) {
    analogWrite(OUT4, LOW);
  } else {
    analogWrite(OUT4, lead2);
  }
}
