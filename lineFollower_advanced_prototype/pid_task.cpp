#include "pid_task.h"

// PID constants
float Kp = 2.0, Ki = 0.0, Kd = 1.0;

volatile int lastError = 0;
volatile float integral = 0.0;

// Motor control pins
const int leftMotor1Pin = 25;
const int leftMotor2Pin = 26;
const int rightMotor1Pin = 27;
const int rightMotor2Pin = 14;

// Function to control motors
void controlMotors(float correction) {
  int baseSpeed = 150; // Base motor speed
  int leftMotorSpeed = baseSpeed + correction;
  int rightMotorSpeed = baseSpeed - correction;

  // Clamp motor speeds
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  // Send speeds to motors
  analogWrite(leftMotor1Pin, leftMotorSpeed);
  analogWrite(leftMotor2Pin, leftMotorSpeed);
  analogWrite(rightMotor1Pin, rightMotorSpeed);
  analogWrite(rightMotor2Pin, rightMotorSpeed);

  // Debug information
  Serial.print("Correction: ");
  Serial.print(correction);
  Serial.print(" Left Motors: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" Right Motors: ");
  Serial.println(rightMotorSpeed);
}

// Task to calculate PID and control motors
void pidTask(void *parameter) {
  pinMode(leftMotor1Pin, OUTPUT);
  pinMode(leftMotor2Pin, OUTPUT);
  pinMode(rightMotor1Pin, OUTPUT);
  pinMode(rightMotor2Pin, OUTPUT);

  for (;;) {
    // PID calculations
    integral += error;
    float derivative = error - lastError;
    float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Control motors
    controlMotors(correction);

    lastError = error;
    delay(50); // Adjust PID update rate
  }
}
