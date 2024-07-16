// 모터 드라이버 핀 정의
#define ENA 9
#define ENB 10
#define IN1 11
#define IN2 12
#define IN3 7
#define IN4 8

// 라인트레이서 센서 핀 정의
#define LEFT_SENSOR_PIN A0
#define LEFT_CENTER_SENSOR_PIN A1
#define RIGHT_CENTER_SENSOR_PIN A3
#define RIGHT_SENSOR_PIN A4

// 고정 속도 정의
#define V 45
#define TURN_V (V - 10) // 회전 시 속도
#define STRONG_TURN_V (V - 20) // 강한 회전 시 속도

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
  pinMode(LEFT_CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  // 시리얼 통신 시작 (디버깅용)
  Serial.begin(9600);
}

void loop() {
  // 센서 값 읽기 (디지털 값으로 변환)
  int leftSensor = digitalRead(LEFT_SENSOR_PIN);
  int leftCenterSensor = digitalRead(LEFT_CENTER_SENSOR_PIN);
  int rightCenterSensor = digitalRead(RIGHT_CENTER_SENSOR_PIN);
  int rightSensor = digitalRead(RIGHT_SENSOR_PIN);

  // 센서 값을 바탕으로 모터 제어
  if ((leftSensor == LOW && leftCenterSensor == LOW) || (rightCenterSensor == LOW && rightSensor == LOW)) {
    // A0, A1이 동시에 감지되거나 A3, A4가 동시에 감지되면 강한 회전
    strongTurn();
  } else if (leftSensor == LOW || leftCenterSensor == LOW) {
    // A0 또는 A1이 감지되면 좌회전
    turnLeft();
  } else if (rightSensor == LOW || rightCenterSensor == LOW) {
    // A3 또는 A4가 감지되면 우회전
    turnRight();
  } else {
    // 아무것도 감지되지 않으면 전진
    moveForward();
  }

  // 디버깅을 위해 센서 값 출력
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(", Left Center: ");
  Serial.print(leftCenterSensor);
  Serial.print(", Right Center: ");
  Serial.print(rightCenterSensor);
  Serial.print(", Right: ");
  Serial.println(rightSensor);

  // 짧은 딜레이 추가하여 반응 속도를 높임
  delay(10);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, V);
  analogWrite(ENB, V);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, TURN_V);
  analogWrite(ENB, TURN_V);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, TURN_V);
  analogWrite(ENB, TURN_V);
}

void strongTurn() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, STRONG_TURN_V);
  analogWrite(ENB, STRONG_TURN_V);
}
