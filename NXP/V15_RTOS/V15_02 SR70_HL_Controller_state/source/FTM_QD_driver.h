/*
 * FTM_QD_driver.h
 *
 *  Created on: Dec 05, 2018
 *      Author: Changhan Jun
 *      PCB version: 12/05/2018
 */

#ifndef FTM_QD_DRIVER_H_
#define FTM_QD_DRIVER_H_

// Definitions for FTM based Quad Encoders
// FTM Default FTM QD modes  =========================================
/* The Flextimer instance/channel used for board only for base 1,2 */

// PCB(V13), FTMs and Decoders share the encoder input pins (total 6, 2 for each Motor)
// Can be switched by the Jumper

// Quadrtic Encoder Channels
#define M1_FTM_BASEADDR FTM1
#define M2_FTM_BASEADDR FTM2

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define QUAD_DECODER_MODULO 65535U // max is 65535 uint16_t

//volatile uint32_t theta_curr = 0U;

/*
ftm_config_t ftmInfo;
ftm_phase_params_t phaseParamsConfigStruct;
*/

//=======================================================


#endif /* FTM_QD_DRIVER_H_ */
