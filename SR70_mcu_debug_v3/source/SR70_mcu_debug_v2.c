/*
 * SR70 Prototype Debugging module
 * Based on PCB Version 14 Dec 05 2018
 *
 *NOTE: Motor driver DRV8834 configuration has been changed. will not work with any prev version.
 *  Created on: Dec 05, 2018
 *      Author: Changhan Jun
 */

 
/**
 * @file    SR70_mcu_debug_v2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKV31F51212.h"
#include "fsl_debug_console.h"
/* cjun*/
#include "RobotInterface.h"

RobotInterface SR70;
/*
 * @brief   Application entry point.
 */

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	// SR70 init cjun
	RobotInterface_Init(&SR70);

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	// SR70 Functions cjun
    	UpdateState(&SR70);
    	ADC_Reading_Test(&SR70);
    	MotorTesting(&SR70);
    	printf("counter 2 is %d \n",GetMotorCounter(&SR70, 2));
    	//PWM_test(&SR70);
    }
    return 0 ;
}
