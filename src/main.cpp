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
const int SERVO_PIN = 4;  // Pin 4 is free - connect orange wire here
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
  // Always start with wheels stopped
  stopMotors();
  
  // Scan left
  sensorServo.write(150);
  delay(300);
  long leftDist = readDistanceCm();
  Serial.print("LEFT: "); Serial.println(leftDist);
  
  // Check if obstacle detected on left
  if (leftDist > 0 && leftDist < 50) {
    Serial.println("Obstacle on LEFT - turning left!");
    turnLeft(200);
    delay(400);
    stopMotors();
    delay(300);
    return;
  }
  
  // Scan center
  sensorServo.write(90);
  delay(300);
  long centerDist = readDistanceCm();
  Serial.print("CENTER: "); Serial.println(centerDist);
  
  // Check if obstacle detected in center
  if (centerDist > 0 && centerDist < 50) {
    Serial.println("Obstacle in CENTER - moving forward!");
    driveForward(180);
    delay(400);
    stopMotors();
    delay(300);
    return;
  }
  
  // Scan right
  sensorServo.write(30);
  delay(300);
  long rightDist = readDistanceCm();
  Serial.print("RIGHT: "); Serial.println(rightDist);
  
  // Check if obstacle detected on right
  if (rightDist > 0 && rightDist < 50) {
    Serial.println("Obstacle on RIGHT - turning right!");
    turnRight(200);
    delay(400);
    stopMotors();
    delay(300);
    return;
  }
  
  // No obstacle detected - center sensor and keep wheels stopped
  sensorServo.write(90);
  stopMotors();
}

void loop() {
  scanAndMove();
  delay(80);
}
