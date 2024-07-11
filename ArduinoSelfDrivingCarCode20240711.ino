// 모터 드라이버 핀 정의
#define ENA 9
#define ENB 10
#define IN1 11
#define IN2 12
#define IN3 7
#define IN4 8

// 2채널 라인트레이서 센서 핀 정의
#define LEFT_SENSOR_PIN A1
#define RIGHT_SENSOR_PIN A3

// 속도 정의
#define V 50

// 센서 임계값 정의
#define THRESHOLD 500

void setup() {
  // 모터 드라이버 핀을 출력 모드로 설정
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // 센서 핀을 입력 모드로 설정
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  // 시리얼 통신 시작
  Serial.begin(9600);
}

void loop() {
  // 각 센서 값 읽기
  int leftSensorValue = analogRead(LEFT_SENSOR_PIN);
  int rightSensorValue = analogRead(RIGHT_SENSOR_PIN);

  // 센서 값 출력
  Serial.print("Left: ");
  Serial.print(leftSensorValue);
  Serial.print(" Right: ");
  Serial.println(rightSensorValue);

  // 센서 값을 바탕으로 모터 제어
  if (leftSensorValue > THRESHOLD && rightSensorValue > THRESHOLD) {
    moveForward(); // 둘 다 라인을 감지하지 못하면 직진
  } else if (leftSensorValue < THRESHOLD && rightSensorValue < THRESHOLD) {
    moveBackward(); // 둘 다 라인을 감지하면 후진
  } else if (leftSensorValue < THRESHOLD) {
    turnLeft(); // 왼쪽 센서가 라인을 감지하면 좌회전
  } else if (rightSensorValue < THRESHOLD) {
    turnRight(); // 오른쪽 센서가 라인을 감지하면 우회전
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, V);
  analogWrite(ENB, V);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, V);
  analogWrite(ENB, V);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, V);
  analogWrite(ENB, V);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, V);
  analogWrite(ENB, V);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
