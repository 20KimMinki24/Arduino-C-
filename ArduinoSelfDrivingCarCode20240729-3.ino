// 센서 핀 번호
const int leftSensorPin = A1;
const int rightSensorPin = A2;

// 속도 설정
const int V = 35;  // 기본 속도 설정
const int speedNormal = V;
const int speedTurn = V;  // 회전 시 속도

// 모터 핀 설정
const int motorENA = 9;
const int motorA1 = 11;
const int motorA2 = 8;
const int motorIN3 = 13;
const int motorIN4 = 12;
const int motorENB = 10;

void setup() {
  // 센서 핀 설정
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  // 모터 핀 설정
  pinMode(motorENA, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);
  pinMode(motorENB, OUTPUT);

  // 초기 모터 속도 설정
  analogWrite(motorENA, speedNormal);
  analogWrite(motorENB, speedNormal);
}

void loop() {
  // 센서 값 읽기
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // 센서 감지 여부에 따른 모터 제어
  if (leftSensorValue == 0 && rightSensorValue == 0) {
    goStraight();
  } else if (leftSensorValue == 0) {
    turnLeft();
  } else if (rightSensorValue == 0) {
    turnRight();
  } else {
    goStraight();
  }

  delay(100);  // 루프 지연
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
  digitalWrite(motorA1, LOW);  // 좌회전 시 왼쪽 모터 정지, 오른쪽 모터 전진
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}

void turnRight() {
  analogWrite(motorENA, speedTurn);
  analogWrite(motorENB, speedTurn);
  digitalWrite(motorA1, HIGH);  // 우회전 시 왼쪽 모터 전진, 오른쪽 모터 정지
  digitalWrite(motorA2, LOW);
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}
