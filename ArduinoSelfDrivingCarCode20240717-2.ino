#define ENA 9
#define ENB 10
#define IN1 11
#define IN2 12
#define IN3 7
#define IN4 8

#define LEFT_SENSOR_PIN A0
#define LEFT_CENTER_SENSOR_PIN A1
#define RIGHT_CENTER_SENSOR_PIN A3
#define RIGHT_SENSOR_PIN A4

#define THRESHOLD 500

#define BASE_SPEED 100
#define TURN_SPEED 70

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(LEFT_CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  int leftSensor = analogRead(LEFT_SENSOR_PIN);
  int leftCenterSensor = analogRead(LEFT_CENTER_SENSOR_PIN);
  int rightCenterSensor = analogRead(RIGHT_CENTER_SENSOR_PIN);
  int rightSensor = analogRead(RIGHT_SENSOR_PIN);

  if (leftCenterSensor < THRESHOLD && rightCenterSensor < THRESHOLD) {
    moveForward();
  } else if (leftSensor < THRESHOLD || leftCenterSensor < THRESHOLD) {
    turnLeft();
  } else if (rightSensor < THRESHOLD || rightCenterSensor < THRESHOLD) {
    turnRight();
  } else {
    moveForward();
  }

  printDebugInfo(leftSensor, leftCenterSensor, rightCenterSensor, rightSensor);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, BASE_SPEED);
  analogWrite(ENB, BASE_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
}

void printDebugInfo(int left, int leftCenter, int rightCenter, int right) {
  Serial.print("Sensors: ");
  Serial.print(left);
  Serial.print(" ");
  Serial.print(leftCenter);
  Serial.print(" ");
  Serial.print(rightCenter);
  Serial.print(" ");
  Serial.println(right);
}