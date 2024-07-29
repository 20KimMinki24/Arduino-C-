const int leftSensorPin = A1;
const int rightSensorPin = A2;
const int V = 35;
const int speedNormal = V;
const int speedTurn = V;
const int motorENA = 9;
const int motorA1 = 11;
const int motorA2 = 8;
const int motorIN3 = 13;
const int motorIN4 = 12;
const int motorENB = 10;

void setup() {
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  pinMode(motorENA, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  pinMode(motorENB, OUTPUT);
  analogWrite(motorENA, speedNormal);
  analogWrite(motorENB, speedNormal);
}

void loop() {
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);
  if (leftSensorValue == 0 && rightSensorValue == 0) {
    goStraight();
  } else if (leftSensorValue == 0) {
    turnLeft();
  } else if (rightSensorValue == 0) {
    turnRight();
  } else {
    goStraight();
  }

}

void goStraight() {
  analogWrite(motorENA, speedNormal);
  analogWrite(motorENB, speedNormal);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}

void turnLeft() {
  analogWrite(motorENA, speedTurn);
  analogWrite(motorENB, speedTurn);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}

void turnRight() {
  analogWrite(motorENA, speedTurn);
  analogWrite(motorENB, speedTurn);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}
