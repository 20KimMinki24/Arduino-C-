// 모터 제어 핀 정의
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

// 적외선 센서 핀 정의
#define IR_LEFT 8
#define IR_RIGHT 9

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // 적외선 센서 핀을 입력으로 설정
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
}

void loop() {
  bool leftSensor = digitalRead(IR_LEFT);
  bool rightSensor = digitalRead(IR_RIGHT);

  if (leftSensor && rightSensor) {
    // 양쪽 센서가 모두 검은 선을 감지한 경우 직진
    moveForward();
  } else if (!leftSensor && rightSensor) {
    // 왼쪽 센서가 흰색을 감지하고 오른쪽 센서가 검은색을 감지한 경우 좌회전
    turnLeft();
  } else if (leftSensor && !rightSensor) {
    // 왼쪽 센서가 검은색을 감지하고 오른쪽 센서가 흰색을 감지한 경우 우회전
    turnRight();
  } else {
    // 양쪽 센서가 모두 흰색을 감지한 경우 멈춤
    stop();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
