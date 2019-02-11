// SR70 Robot
// State debugging module

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"


/* Demo includes. */
#include "supporting_functions.h"

// Robot

#include "RobotInterface.h"

RobotInterface SR70;

int  i = 0;

/* The task functions. */

void vPeriodicTask( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */

const char *pcTextForPeriodicTask = "Periodic task is running\r\n";


// RTOS Handler

TaskHandle_t m_Home_task;

/*-----------------------------------------------------------*/

int main( void )
{
	//RobotInterface_Init(&SR70);

	/* Create two instances of the continuous processing task, both at priority	1. */
	

	/* Create one instance of the periodic task at priority 2. */

	//xTaskCreate(vContinuousProcessingTask, "Task 1", 1000, NULL, 3,&m_Home_task);
	xTaskCreate( vPeriodicTask, "Task 3", 1000, (void*)pcTextForPeriodicTask, 2, NULL );

	/* Start the scheduler to start the tasks executing. */
	vTaskStartScheduler();

	/* The following line should never be reached because vTaskStartScheduler()
	will only return if there was not enough FreeRTOS heap memory available to
	create the Idle and (if configured) Timer tasks.  Heap management, and
	techniques for trapping heap exhaustion, are described in the book text. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

void vPeriodicTask( void *pvParameters )
{
TickType_t xLastWakeTime;
const TickType_t xDelay5ms = pdMS_TO_TICKS( 5UL );

	/* The xLastWakeTime variable needs to be initialized with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */


	while(1)
	{
		i++;
		if (i > 100)
		{
			xTaskCreate(vContinuousProcessingTask, "Task 1", 1000, NULL, 3, &m_Home_task);
			i = 0;
		}
		/* Print out the name of this task. */
		vPrintString( "Periodic task is running\r\n" );

		/* We want this task to execute exactly every 10 milliseconds. */
		vTaskDelayUntil( &xLastWakeTime, xDelay5ms );
	}
}

void vContinuousProcessingTask(void *pvParameters)
{
	vPrintString("Cont task is running\r\n");
	while (1)
	{
		vPrintString("Cont task is running\r\n");
		i++;
		if (i > 1000) {
			vTaskDelete(m_Home_task);

		}
	}
}


