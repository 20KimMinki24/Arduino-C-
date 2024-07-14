// 모터 드라이버 핀 정의
#define ENA 9
#define ENB 10
#define IN1 11
#define IN2 12
#define IN3 7
#define IN4 8

// 라인트레이서 센서 핀 정의
#define LEFT_SENSOR_PIN A0
#define LSP A1
#define RSP A3
#define RIGHT_SENSOR_PIN A4

// 속도 정의
#define V 38

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
  pinMode(LSP, INPUT);
  pinMode(RSP, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  // 시리얼 통신 시작 (디버깅용)
  Serial.begin(9600);
}

void loop() {
  // 각 센서 값 읽기
  int leftSensor = digitalRead(LEFT_SENSOR_PIN);
  int leftCenterSensor = digitalRead(LSP);
  int rightCenterSensor = digitalRead(RSP);
  int rightSensor = digitalRead(RIGHT_SENSOR_PIN);
  
  // 센서 값을 바탕으로 모터 제어
  if (((leftSensor == LOW) || (leftCenterSensor == LOW)) && ((rightSensor == LOW) || (rightCenterSensor == LOW))) {
    moveForward();
  } else if ((leftSensor == HIGH) && (leftCenterSensor == HIGH) && (rightSensor == HIGH) && (rightCenterSensor == HIGH)) {
    moveForward();
  } else {
    if (leftSensor == LOW || leftCenterSensor == LOW) {
      turnLeft();
    } 
    if (rightSensor == LOW || rightCenterSensor == LOW) {
      turnRight();
    }
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, V-5);
  analogWrite(ENB, V-5);
}

void turnLeft() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, V+20);
  analogWrite(ENB, V+20);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, V+20);
  analogWrite(ENB, V+20);
}
