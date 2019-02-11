/*
 * SR70 Prototype Debugging module
 * Based on PCB Version 13 Dec 05 2018
 *
 *  Created on: Dec 05, 2018
 *      Author: Changhan Jun
 */

 
/**
 * @file    SR70_mcu_debug_v2.c
 * @brief   Application entry point.
 */

// important note : for PCB v13, motor 1 does not work properly, FTM base and channel of motor 1 and 3 are exchanged
// FTM base 3 is used for timer
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKV31F51212.h"
#include "fsl_debug_console.h"
/* cjun*/
#include "RobotInterface.h"

RobotInterface SR70; // robot object

/*******************************************************************************
 * FTM Timer Variables
 ******************************************************************************/
#define BOARD_FTM_BASEADDR FTM3
#define BOARD_FTM_IRQ_NUM FTM3_IRQn
#define BOARD_FTM_HANDLER FTM3_IRQHandler
/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK3 (CLOCK_GetFreq(kCLOCK_BusClk)/4)
volatile bool ftmIsrFlag = false;
volatile uint32_t milisecondCounts = 0U;
/*******************************************************************************/

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	//========== Timer Init Cjun

    uint32_t delT = 50U; // [msec]
    ftm_config_t ftmInfo;

    FTM_GetDefaultConfig(&ftmInfo);
    ftmInfo.prescale = kFTM_Prescale_Divide_4;
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);
    FTM_SetTimerPeriod(BOARD_FTM_BASEADDR, USEC_TO_COUNT(1000U, FTM_SOURCE_CLOCK3)); // 1micro sec to count
    FTM_EnableInterrupts(BOARD_FTM_BASEADDR, kFTM_TimeOverflowInterruptEnable);
    EnableIRQ(BOARD_FTM_IRQ_NUM);
    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
	//==============================
	// SR70 init cjun
	RobotInterface_Init(&SR70);
	int test = 2;
	int ADC_0[3] ={0};
	int ADC_1[3] ={0};

    while(1) {
    	// SR70 Functions CJun
    	UpdateState(&SR70);

    	// ADC Calibration


    	if (ftmIsrFlag)
    	        {
    	            milisecondCounts++;
    	            ftmIsrFlag = false;
    	            if (milisecondCounts >= delT) // timer period
    	            {

    	            	// 02. INPUT Test
    	            	if(test == 2){
    	            	printf("=================\n");
    	            	printf("ADC 1 Reading is %d \n", SR70.ADC_data[0]);
    	            	printf("=================\n");
    	            	printf("ADC 2 Reading is %d \n", SR70.ADC_data[1]);
    	            	printf("=================\n");
    	            	if(SR70.sbtn[0]){printf("Side button 1 is pressed");}
    	            	if(SR70.sbtn[1]){printf("Side button 2 is pressed");}}


    	            	if (test == 5){
    	            	ReadQDCountsPractical(&SR70); // sampling time should be fast enough that it updates counts < 2^8 in delT
    	            	MotorPathPlanning(&SR70);
    	            	MotorPositionControl(&SR70,delT);}

    	            	milisecondCounts = 0U;

    	            }
    	        }
    }
    return 0 ;
}
void BOARD_FTM_HANDLER(void)
{
  // FTM3 interrupt
    FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, kFTM_TimeOverflowFlag);
    ftmIsrFlag = true;
}
