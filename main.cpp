#include <Arduino.h>
#include <Servo.h>

// Motor pins (UNO)
const int in1 = 8; // left motor A
const int in2 = 9; // left motor B
const int in3 = 10; // right motor A
const int in4 = 11; // right motor B
const int ena = 5; // left PWM
const int enb = 6; // right PWM

// Ultrasonic sensor
const int TRIG = 12;
const int ECHO = 13;

// Servo for scanning
const int SERVO_PIN = 3;
Servo sensorServo;

// Behavior thresholds (cm)
const int SAFE_DISTANCE = 30; // drive forward above this
const int SLOW_DISTANCE = 15; // slow/prepare below this

void setup() {
  Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  sensorServo.attach(SERVO_PIN);
  sensorServo.write(90);

  Serial.println("Follow/avoid starting. Keep motor battery disconnected while uploading.");
  delay(200);
}

long readDistanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return -1;
  return duration / 58.2;
}

void driveForward(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void turnLeft(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void turnRight(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void scanAndMove() {
  sensorServo.write(150);
  delay(350);
  long leftDist = readDistanceCm();

  sensorServo.write(90);
  delay(350);
  long centerDist = readDistanceCm();

  sensorServo.write(30);
  delay(350);
  long rightDist = readDistanceCm();

  sensorServo.write(90);

  if (leftDist < 0) leftDist = 200;
  if (centerDist < 0) centerDist = 200;
  if (rightDist < 0) rightDist = 200;

  Serial.print("L:"); Serial.print(leftDist);
  Serial.print("  C:"); Serial.print(centerDist);
  Serial.print("  R:"); Serial.println(rightDist);

  if (centerDist <= SLOW_DISTANCE) {
    stopMotors();
    delay(150);

    if (leftDist >= rightDist) {
      Serial.println("Obstacle ahead: turning left");
      turnLeft(180);
    } else {
      Serial.println("Obstacle ahead: turning right");
      turnRight(180);
    }

    delay(450);
    stopMotors();
    delay(150);
    return;
  }

  if (centerDist > SAFE_DISTANCE) {
    driveForward(200);
  } else {
    driveForward(120);
  }
}

void loop() {
  scanAndMove();
  delay(80);
}
