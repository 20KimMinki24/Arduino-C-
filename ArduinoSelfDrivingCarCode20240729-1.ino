const int sensorCount = 8;
const int sensorPins[sensorCount] = {2, 3, A2, A3, A4, A5, 4, 5};  // 센서 핀 배열

// 속도 설정
const int V = 35;  // 속도를 35로 설정
const int speedNormal = V;
const int speedTurn = V;  // 회전 시 속도 (급커브와 동일하게 처리)

// 모터 핀 설정
const int motorENA = 9;
const int motorA1 = 11;
const int motorA2 = 8;
const int motorIN3 = 13;
const int motorIN4 = 12;
const int motorENB = 10;

void setup() {
  // 센서 핀 설정
  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensorPins[i], INPUT);
  }

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
  int sensorValues[sensorCount];
  for (int i = 0; i < sensorCount; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
  }

  // 센서 감지 여부
  bool leftDetected = sensorValues[0] == 0 || sensorValues[1] == 0 || sensorValues[2] == 0 || sensorValues[3] == 0;
  bool rightDetected = sensorValues[4] == 0 || sensorValues[5] == 0 || sensorValues[6] == 0 || sensorValues[7] == 0;

  if (leftDetected && rightDetected) {
    goStraight();
  } else if (leftDetected) {
    turnLeft();
  } else if (rightDetected) {
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
  digitalWrite(motorA1, HIGH);  // 왼쪽 회전
  digitalWrite(motorA2, LOW);
  digitalWrite(motorIN3, LOW);
  digitalWrite(motorIN4, HIGH);
}

void turnRight() {
  analogWrite(motorENA, speedTurn);
  analogWrite(motorENB, speedTurn);
  digitalWrite(motorA1, LOW);  // 오른쪽 회전
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorIN3, HIGH);
  digitalWrite(motorIN4, LOW);
}
