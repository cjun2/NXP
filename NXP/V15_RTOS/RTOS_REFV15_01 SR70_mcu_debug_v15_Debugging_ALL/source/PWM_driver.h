/*
 * FTM_driver.h
 *
 *  Created on: Dec 05, 2018
 *      Author: changhan
 *      PCB version: 12/05/2018
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_
/*******************************************************************************
 *  PWM(FTM) Definitions
 ******************************************************************************/
#define BOARD_FTM_BASEADDR1 FTM0 // M1 PTA4
#define BOARD_FTM_BASEADDR2 FTM0 // M2 PTC4
#define BOARD_FTM_BASEADDR3 FTM0 // M3 PTC3

#define BOARD_FTM_CHANNEL1 kFTM_Chnl_1
#define BOARD_FTM_CHANNEL1b kFTM_Chnl_0 // updated for pcb 15 1/23/2019

#define BOARD_FTM_CHANNEL2 kFTM_Chnl_3
#define BOARD_FTM_CHANNEL2b kFTM_Chnl_6// updated for pcb 15 1/23/2019

#define BOARD_FTM_CHANNEL3 kFTM_Chnl_2
#define BOARD_FTM_CHANNEL3b kFTM_Chnl_7// updated for pcb 15 1/23/2019

#define FTM_CHANNEL_FLAG1 kFTM_Chnl1Flag
#define FTM_CHANNEL_FLAG1b kFTM_Chnl0Flag// updated for pcb 15 1/23/2019

#define FTM_CHANNEL_FLAG2 kFTM_Chnl3Flag
#define FTM_CHANNEL_FLAG2b kFTM_Chnl6Flag// updated for pcb 15 1/23/2019

#define FTM_CHANNEL_FLAG3 kFTM_Chnl2Flag
#define FTM_CHANNEL_FLAG3b kFTM_Chnl7Flag// updated for pcb 15 1/23/2019
/*******************************************************************************
 *  PWM(FTM) Definitions - Debugged
 ******************************************************************************/
/*
// Base all 0
#define BOARD_FTM_BASEADDR1 FTM0
#define BOARD_FTM_BASEADDR2 FTM0
//#define BOARD_FTM_BASEADDR3 FTM1 // config FTM base door for 0,1
#define BOARD_FTM_BASEADDR3 FTM0

//#define BOARD_FTM_CHANNEL2 kFTM_Chnl_3

#define BOARD_FTM_CHANNEL1 kFTM_Chnl_4 // Temporary for PTD4, PTA4:FTM0 1
#define BOARD_FTM_CHANNEL2 kFTM_Chnl_3
#define BOARD_FTM_CHANNEL3 kFTM_Chnl_2

#define FTM_CHANNEL_INTERRUPT_ENABLE kFTM_Chnl7InterruptEnable
//#define FTM_CHANNEL_FLAG2 kFTM_Chnl3Flag
#define FTM_CHANNEL_FLAG2 kFTM_Chnl2Flag
#define FTM_CHANNEL_FLAG3 kFTM_Chnl1Flag

// Interrupt number and interrupt handler for the FTM base address used
#define FTM_INTERRUPT_NUMBER2 FTM0_IRQn
#define FTM_INTERRUPT_NUMBER3 FTM1_IRQn

#define FTM_2_HANDLER FTM0_IRQHandler
#define FTM_3_HANDLER FTM1_IRQHandler

// Interrupt to enable and flag to read
#define FTM_CHANNEL_INTERRUPT_ENABLE2 kFTM_Chnl3InterruptEnable
#define FTM_CHANNEL_INTERRUPT_ENABLE3 kFTM_Chnl1InterruptEnable
*/
/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)


#endif /* PWM_DRIVER_H_ */
