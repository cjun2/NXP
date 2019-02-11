/*
 * GPIOs_driver.h
 *		Dec 05, 2018
 *      Author: changhan
 *      PCB Version: 12/05/2018
 */

#ifndef GPIOS_DRIVER_H_
#define GPIOS_DRIVER_H_

/*******************************************************************************
 *  Digital Out Definitions GPIO - Motor directions
 ******************************************************************************/
//M1 Dir1 -> PTC1
#define Board_GPIO_DIR_M1 GPIOC
#define Board_DIR_M1_1 1U
//M1 Dir2 -> PTB20
#define Board_GPIO_DIR2_M1 GPIOB
#define Board_DIR_M1_2 20U

//M2 Dir -> PTB21
#define Board_GPIO_DIR_M2 GPIOB
#define Board_DIR_M2_1 21U
//M2 Dir2 -> PTB22
#define Board_GPIO_DIR2_M2 GPIOB
#define Board_DIR_M2_2 22U

//M3 Dir -> PTB 10
#define Board_GPIO_DIR_M3 GPIOB
#define Board_DIR_M3_1 10U
//M3 Dir2 -> PTB 10
#define Board_GPIO_DIR2_M3 GPIOB
#define Board_DIR_M3_2 9U


/*******************************************************************************
 * Side Button Definitions GPIO - /Buttons
 ******************************************************************************/
#define SBTN_Board_base GPIOB
#define SBTN_Port_base PORTB
#define SideBtn1_Pin 2U // PTB 2
#define SideBtn2_Pin 3U // PTB 3

// in case of interrupts : not used here yet
#define SBTN_IRQ PORTB_IRQn
#define SBTN_IRQhandler PORTB_IRQHandler
/*******************************************************************************
 * Joystick Button Definitions GPIO - /Buttons : disabled
 ******************************************************************************/
#define JOYBTN_Board_base GPIOC
#define JOYBTN_Port_base PORTC
#define JoyBtn_Pin 8U


#endif /* GPIOS_DRIVER_H_ */
