#include "core_assigner.h"
#include "ir_sensor_task.h"
#include "pid_task.h"
#include "shared_data.h"

void setup() {
  Serial.begin(115200);

  // Assign tasks to cores
  assignToCore1(irSensorTask, "IR Sensor Task", 10000, NULL, 1);
  assignToCore2(pidTask, "PID Task", 10000, NULL, 0);
}

void loop() {
  // Main loop can handle additional tasks & debugs if needed
  delay(1000);
}
