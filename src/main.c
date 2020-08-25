#include "CMSDK_CM3.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#define TASK_A_PRIORITY				(tskIDLE_PRIORITY + 1)

void TaskA( void *pvParameters )
{
	const TickType_t x500ms = pdMS_TO_TICKS(500);

	while(1) {
		CMSDK_GPIO0->DATAOUT ^= 1;		// GPIO Toggle
		vTaskDelay(x500ms);
	}
}

int main()
{
	CMSDK_GPIO0->OUTENABLESET = 1;		// GPIO Out
	
	xTaskCreate(TaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, \
				TASK_A_PRIORITY, (TaskHandle_t *)NULL);

	vTaskStartScheduler();
}
