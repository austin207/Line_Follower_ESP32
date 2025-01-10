# Project: Advanced Line Follower Prototype

## Overview
This project involves developing an advanced line-following robot using an ESP32 microcontroller. The system employs multitasking capabilities of the ESP32 to handle multiple tasks concurrently, including IR sensor data collection and PID control for precise motor movement. The implementation uses FreeRTOS for task management, allowing efficient handling of real-time constraints.

---

## Project Structure
### Files and Directories
1. **Main Sketch File**: `lineFollower_advanced_prototype.ino`
   - Entry point of the project, initializes tasks and FreeRTOS setup.
2. **Task Headers and Implementations**:
   - `IR_SENSOR_TASK`
     - Header: `ir_sensor_task.h`
     - Implementation: `ir_sensor_task.cpp`
   - `PID_TASK`
     - Header: `pid_task.h`
     - Implementation: `pid_task.cpp`
3. **Shared Data**:
   - Header: `shared_data.h`
   - Implementation: `shared_data.cpp`
     - Defines shared variables such as `volatile int error` used across tasks.
4. **Core Assigner**:
   - Header: `core_assigner.h`
     - Functions for assigning tasks to specific ESP32 cores.

---

## Key Features
### Multitasking with FreeRTOS
- Tasks are created using FreeRTOS’s `xTaskCreatePinnedToCore()` function to pin tasks to specific cores.
- Separate tasks for:
  1. **IR Sensor Data Collection**: Reads sensor values and calculates errors.
  2. **PID Control**: Processes the error values and calculates motor adjustments.

### Shared Data Management
- `volatile int error`: A global variable shared between tasks to ensure real-time updates.
- Proper separation of declaration and definition:
  - Declared in `shared_data.h` using `extern`.
  - Defined in `shared_data.cpp`.

### Core Assignment
- Utilizes `core_assigner.h` to allocate tasks to specific cores (Core 0 and Core 1), ensuring optimal resource usage.

---

## Implementation Details
### `shared_data.h` and `shared_data.cpp`
- **Purpose**: Manages shared variables accessed by multiple tasks.
- **Key Variable**:
  - `volatile int error`: Tracks the error calculated by the IR sensor task.
- **Correct Setup**:
  - Declared as `extern volatile int error` in `shared_data.h`.
  - Defined once in `shared_data.cpp`:
    ```cpp
    #include "shared_data.h"
    volatile int error = 0;
    ```

### Core Assigner (`core_assigner.h`)
- Provides functions for assigning tasks to specific ESP32 cores.
- Example Usage:
  ```cpp
  assignToCore1(irSensorTask, "IR Sensor Task", 2048, NULL, 1);
  assignToCore2(pidTask, "PID Task", 2048, NULL, 1);
  ```
- Functions:
  - `assignToCore1()`: Assigns a task to Core 1.
  - `assignToCore2()`: Assigns a task to Core 2.

### Task Implementations
#### IR Sensor Task (`ir_sensor_task.cpp`)
- Reads IR sensor values to calculate the error.
- Updates the `error` variable in `shared_data.h`.

#### PID Task (`pid_task.cpp`)
- Implements a PID controller to process the error and adjust motor speeds.

### Main Sketch (`lineFollower_advanced_prototype.ino`)
- **Initialization**:
  - Includes necessary headers.
  - Sets up shared variables.
  - Creates tasks using `xTaskCreatePinnedToCore()`.
- **Task Creation Example**:
  ```cpp
  assignToCore1(irSensorTask, "IR Sensor Task", 2048, NULL, 1);
  assignToCore2(pidTask, "PID Task", 2048, NULL, 1);
  ```

---

## Troubleshooting and Debugging
### Compilation Issues
1. **Error**: Multiple definition of `error`.
   - Cause: The `error` variable was defined in multiple files.
   - Solution:
     - Declare `error` as `extern` in `shared_data.h`.
     - Define it only in `shared_data.cpp`.

2. **Error**: Missing `core_assigner.h`.
   - Cause: Header file not included in the sketch.
   - Solution: Include the header in `lineFollower_advanced_prototype.ino`.

### Runtime Issues
1. **Tasks Not Running Properly**:
   - Ensure tasks are correctly assigned to cores.
   - Verify stack size and priority during task creation.
2. **Motor Driver Resets ESP32**:
   - Use diodes to prevent backflow of voltage.
   - Power the motor driver logic separately from the ESP32.

---

## Key Learnings
1. **Task Management**:
   - FreeRTOS allows for efficient task management on the ESP32’s dual-core architecture.
2. **Shared Data Handling**:
   - Proper separation of declaration (`extern`) and definition for shared variables is crucial to avoid linker errors.
3. **Debugging**:
   - Systematic debugging by isolating issues in compilation and runtime.
4. **Power Management**:
   - Proper isolation of power supplies prevents hardware resets.

---

## Teaching Points
1. **Multitasking Basics**:
   - Explain FreeRTOS task creation and core assignment.
2. **Shared Variable Management**:
   - Demonstrate the use of `extern` for shared data across files.
3. **System Architecture**:
   - Show the project’s modular structure with separate tasks and shared data management.
4. **Debugging Techniques**:
   - Guide through troubleshooting steps for common issues.

---

## Conclusion
This project showcases the efficient use of ESP32’s multitasking capabilities for real-time robotics applications. By structuring tasks properly, managing shared data efficiently, and using the FreeRTOS framework, the line-following robot achieves precise and responsive movement. The detailed modular structure makes it easy to maintain and expand upon, providing an excellent learning opportunity for team members and colleagues.

