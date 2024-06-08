#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/psram.h"
#include "esp_heap_caps.h"

// 假设你已经初始化了外部 RAM (psram_init())

// 任务函数
void myTask(void *pvParameters)
{
    // 任务代码...
}

void app_main()
{
    // 初始化外部 RAM（如果还没做的话）
    psram_init();

    // 分配外部 RAM 作为任务堆栈
    size_t stackSize = 4096; // 例如，4KB 的堆栈大小
    void *externalStack = heap_caps_malloc(stackSize, MALLOC_CAP_PSRAM);
    if (externalStack == NULL) {
        // 错误处理
        return;
    }

    // 创建任务，使用外部 RAM 中的堆栈
    TaskHandle_t taskHandle;
    StackType_t *stackBuffer = (StackType_t *)externalStack;
    const TaskFunction_t taskFunction = myTask;
    const char *taskName = "MyTask";
    uint32_t priority = 5;
    TaskParams_t taskParams = { .stackDepth = stackSize, .inputParameter = NULL };

    if (xTaskCreateStatic(taskFunction, taskName, stackSize, NULL, priority, taskHandle, stackBuffer, NULL) != pdPASS) {
        // 错误处理
        heap_caps_free(externalStack); // 释放外部 RAM 中的堆栈
        return;
    }

    // 启动调度器
    vTaskStartScheduler();

    // 如果调度器正确启动，这行代码不会执行
    for (;;) {
        // 如果需要的话，在这里执行一些任务
    }
}