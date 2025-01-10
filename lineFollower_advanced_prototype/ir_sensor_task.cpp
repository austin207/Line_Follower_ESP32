#include "ir_sensor_task.h"

// IR sensor pins
const int leftIRPin = 33;
const int centerIRPin = 32;
const int rightIRPin = 35;

// Task to read IR sensors and calculate error
void irSensorTask(void *parameter) {
  pinMode(leftIRPin, INPUT);
  pinMode(centerIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  for (;;) {
    int leftValue = digitalRead(leftIRPin);
    int centerValue = digitalRead(centerIRPin);
    int rightValue = digitalRead(rightIRPin);

    // Calculate error based on sensor values
    if (centerValue == HIGH) {
      error = 0;
    } else if (leftValue == HIGH) {
      error = -1;
    } else if (rightValue == HIGH) {
      error = 1;
    } else {
      error = 0;
    }

    // Debug information
    Serial.print("Left: ");
    Serial.print(leftValue);
    Serial.print(" Center: ");
    Serial.print(centerValue);
    Serial.print(" Right: ");
    Serial.print(rightValue);
    Serial.print(" Error: ");
    Serial.println(error);

    delay(10); // Adjust sensor reading frequency
  }
}
