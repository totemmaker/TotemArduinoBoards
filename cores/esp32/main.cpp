#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "Arduino.h"

#ifndef CONFIG_ARDUINO_LOOP_STACK_SIZE
#define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192
#endif

TaskHandle_t loopTaskHandle = NULL;

#if CONFIG_AUTOSTART_ARDUINO

bool loopTaskWDTEnabled;

void loopTask(void *pvParameters)
{
    setup();
    for(;;) {
        if(loopTaskWDTEnabled){
            esp_task_wdt_reset();
        }
        loop();
        if (serialEventRun) serialEventRun();
    }
}

extern "C" void app_main()
{
    loopTaskWDTEnabled = false;
    initArduino();
    xTaskCreateUniversal(loopTask, "loopTask", CONFIG_ARDUINO_LOOP_STACK_SIZE, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
}

void extraLoopTask(void *pvParameters)
{
    void (*extraLoop)(void) = (void (*)(void))pvParameters;
    for(;;) {
        extraLoop();
    }
}

void addLoop(void (*loopFunc)(void)) {
    // Count number of created tasks
    static uint8_t taskCount = 0;
    taskCount++;
    // Prepare task name
    char taskName[configMAX_TASK_NAME_LEN] = "loopTask";
    // Add task number to name
    if (taskCount >= 10) {
        taskName[8] = '0' + (taskCount / 10);
        taskName[9] = '0' + (taskCount % 10);
        taskName[10] = '\n';
    }
    else {
        taskName[8] = '0' + (taskCount % 10);
        taskName[9] = '\n';
    }
    // Create task
    xTaskCreateUniversal(extraLoopTask, taskName, CONFIG_ARDUINO_LOOP_STACK_SIZE, (void*)loopFunc, 1, nullptr, CONFIG_ARDUINO_RUNNING_CORE);
}

#endif
