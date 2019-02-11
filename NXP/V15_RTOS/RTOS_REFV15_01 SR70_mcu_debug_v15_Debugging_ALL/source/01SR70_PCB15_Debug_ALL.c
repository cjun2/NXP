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
 * LED Blinking
 ******************************************************************************/
#define BOARD_HB_LED_GPIO GPIOA
#define BOARD_HB_LED_GPIO_PIN 13U
void IRQhandler(void) // interrupt from GPIO D4,5
{
	GPIO_PortClearInterruptFlags(Decoder3_Board_base, 1U << Decoder3_Down_Pin);
	printf("Interrupt Ch # is : %d \n",GPIO_PortGetInterruptFlags ( Decoder3_Board_base));// returns pin#

#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
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

//debug
volatile uint32_t delTCounts = 0U;
volatile uint32_t WDCounts =0U;
int dr = 1;
int sig=99;

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
	// =====blinking Test Functions ======================


		gpio_pin_config_t Decode_config = {
		        kGPIO_DigitalInput, 0,
		    };
		 gpio_pin_config_t led_config = {
		            kGPIO_DigitalOutput, 0,
		        };
		        printf("Custom MCU Testing \n");
		        // Init output LED GPIO.
		        GPIO_PinInit(BOARD_HB_LED_GPIO, BOARD_HB_LED_GPIO_PIN, &led_config);

		       // RobotInterface_Init(&SR70);
		       GPIO_PortToggle(BOARD_HB_LED_GPIO, 1u << BOARD_HB_LED_GPIO_PIN);
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
	int test = 5;

	if (test == 6 ){
	int32_t target[3];
	target [0]=322785*3;
	target [1]=322785*2;target [2]=0;
	SetTarget(&SR70,target); }

    while(1) {
    	// SR70 Functions CJun
    	UpdateState(&SR70);

    	if (ftmIsrFlag)
    	        {
    	            milisecondCounts++;
    	            ftmIsrFlag = false;
    	            if (milisecondCounts >= delT) // timer period
    	            {
    	            	// 01. LED Blinking
    	            	if (test == 1){
    	            	GPIO_PortToggle(BOARD_HB_LED_GPIO, 1u << BOARD_HB_LED_GPIO_PIN);}

    	            	// 02. INPUT Test
    	            	if(test == 2){
    	            	printf("=================\n");
    	            	printf("ADC 1 Reading is %d \n", SR70.ADC_data[0]);
    	            	printf("=================\n");
    	            	printf("ADC 2 Reading is %d \n", SR70.ADC_data[1]);
    	            	printf("=================\n");
    	            	if(SR70.sbtn[0]){printf("Side button 1 is pressed");}
    	            	if(SR70.sbtn[1]){printf("Side button 2 is pressed");}}

    	            	// 03. Motor Breaking Test
    	            	if(test == 3){
						int dir[3]; int Sigs[3];
						for (int i=0;i<3;i++){dir[i]=1;Sigs[i]=90;}
						MotorCommand (&SR70, dir, Sigs);}

    	            	// 04. Motor running
    	            	if(test == 4){
    	            	int dir[3]; int Sigs[3];
    	            	for (int i=0;i<3;i++){dir[i]=dr;Sigs[i]=sig;}
    	            	delTCounts++;
    	            	if (delTCounts >=15){dr=-1*dr;delTCounts = 0U;
    	            		if(sig <5){sig=99;}else{sig=sig-5;}
    	            	} // every 5sec
    	            	/*WDCounts++;
    	            	if(WDCounts >= 50){
    	            		printf("All Are Fine \n ");
    	            		 WDCounts = 0U;
    	            	}*/
    	            	MotorCommand (&SR70, dir, Sigs);}

    	            	// 05. M1/M2 Pos Control
    	            	if (test == 5){
    	            	ReadQDCountsPractical(&SR70); // sampling time should be fast enough that it updates counts < 2^8 in delT
    	            	MotorPathPlanning(&SR70);
    	            	MotorPositionControl(&SR70,delT);}

    	            	if (test == 6){
    	            	    	            	ReadQDCountsPractical(&SR70); // sampling time should be fast enough that it updates counts < 2^8 in delT
    	            	    	            	//MotorLifeCycleRunning(&SR70);
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
