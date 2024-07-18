#define ENA 9
#define ENB 10
#define IN1 11
#define IN2 12
#define IN3 7
#define IN4 8

#define LEFT_SENSOR_PIN 2
#define LEFT_CENTER_SENSOR_PIN 3
#define RIGHT_CENTER_SENSOR_PIN 4
#define RIGHT_SENSOR_PIN 5

#define MAX_SPEED 50
#define BASE_SPEED 40

volatile bool leftSensor = false;
volatile bool leftCenterSensor = false;
volatile bool rightCenterSensor = false;
volatile bool rightSensor = false;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LEFT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LEFT_CENTER_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RIGHT_CENTER_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RIGHT_SENSOR_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR_PIN), leftSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEFT_CENTER_SENSOR_PIN), leftCenterSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_CENTER_SENSOR_PIN), rightCenterSensorISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR_PIN), rightSensorISR, CHANGE);

  Serial.begin(115200);
  
  // 모터 테스트
  testMotors();
}

void loop() {
  // 센서 상태 출력
  printSensorStatus();
  
  if (leftSensor || leftCenterSensor) {
    Serial.println("Turning Left");
    turnLeft();
  } else if (rightSensor || rightCenterSensor) {
    Serial.println("Turning Right");
    turnRight();
  } else {
    Serial.println("Moving Forward");
    moveForward();
  }
  
  delay(100);  // 짧은 지연 추가
}

void printSensorStatus() {
  Serial.print("Sensors: L:");
  Serial.print(leftSensor);
  Serial.print(" LC:");
  Serial.print(leftCenterSensor);
  Serial.print(" RC:");
  Serial.print(rightCenterSensor);
  Serial.print(" R:");
  Serial.println(rightSensor);
}

void leftSensorISR() {
  leftSensor = !digitalRead(LEFT_SENSOR_PIN);
}

void leftCenterSensorISR() {
  leftCenterSensor = !digitalRead(LEFT_CENTER_SENSOR_PIN);
}

void rightCenterSensorISR() {
  rightCenterSensor = !digitalRead(RIGHT_CENTER_SENSOR_PIN);
}

void rightSensorISR() {
  rightSensor = !digitalRead(RIGHT_SENSOR_PIN);
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
  analogWrite(ENA, BASE_SPEED);
  analogWrite(ENB, BASE_SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, BASE_SPEED);
  analogWrite(ENB, BASE_SPEED);
}

void testMotors() {
  Serial.println("Testing motors...");
  
  Serial.println("Moving forward");
  moveForward();
  delay(2000);
  
  Serial.println("Turning left");
  turnLeft();
  delay(2000);
  
  Serial.println("Turning right");
  turnRight();
  delay(2000);
  
  Serial.println("Stopping");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  Serial.println("Motor test complete");
}