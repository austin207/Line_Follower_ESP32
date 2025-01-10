#ifndef CORE_ASSIGNER_H
#define CORE_ASSIGNER_H

#include "Arduino.h"

// Task handles
TaskHandle_t Core1TaskHandle;
TaskHandle_t Core2TaskHandle;

// Function to assign a task to Core 1 (Core 0)
void assignToCore1(void (*task)(void *), const char *taskName, uint32_t stackSize, void *params, UBaseType_t priority) {
    xTaskCreatePinnedToCore(
        task,             // Task function
        taskName,         // Task name
        stackSize,        // Stack size
        params,           // Parameters
        priority,         // Priority
        &Core1TaskHandle, // Task handle
        0                 // Core 0
    );
}

// Function to assign a task to Core 2 (Core 1)
void assignToCore2(void (*task)(void *), const char *taskName, uint32_t stackSize, void *params, UBaseType_t priority) {
    xTaskCreatePinnedToCore(
        task,             // Task function
        taskName,         // Task name
        stackSize,        // Stack size
        params,           // Parameters
        priority,         // Priority
        &Core2TaskHandle, // Task handle
        1                 // Core 1
    );
}

#endif
