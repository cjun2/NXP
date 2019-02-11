/*
 * RobotInterface.h
 *
 *  Created on: Nov 29, 2018
 *      Author: Changhan Jun
 */

#ifndef ROBOTINTERFACE_H_
#define ROBOTINTERFACE_H_



#include "fsl_adc16.h"
#include "board.h"
#include "fsl_ftm.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#include "ADC_driver.h" // includes ADC definitions
#include "GPIOs_driver.h" // includes GPIOs definitions
#include <PWM_driver.h> // includes FTM (PWM) definitions
#include <FTM_QD_driver.h> // include FTM QD definitions

#include "DC_Motor.h"
// ===== Robotic System Configuration Definitions========================
#define d_motors	3	// # of motor axes
#define	d_ADCi	2	// # of ADC inputs
#define	d_Di	2 // # of digital inputs
// ===== Robot Status & Commands Definitions========================
#define ROBOT_MCUOFF	-11
#define ROBOT_OFF	-10
#define ROBOT_STOP	-1
#define ROBOT_READY 0
#define ROBOT_MOVE	1
#define ROBOT_HOME	2

// Robot Status & Commands Struct
typedef struct STATE STATE;
struct STATE{
		short status, command;
};

typedef struct RobotInterface RobotInterface;

struct RobotInterface {
	// motor instances
	DC_Motor m_motors[d_motors];
	// State command
	STATE m_state;
	// UI- Input state
	int ADC_data[d_ADCi]; // reading value from Joysticks 0 - 4096
	int sbtn[d_Di];	// reading value from Side buttons 0-1
	unsigned int M_Sig[d_motors]; // motor outputs
	double encoderCnt[d_motors];
	int joybtn;

	bool ADC_init,	PWM_init,	GPIO_init;
	// ADC config instances
	adc16_config_t adc16ConfigStruct;
	adc16_channel_config_t adc16ChannelConfigStruct;
	adc16_channel_config_t adc16ChannelConfigStruct2;
	// PWM config instances

	//FTM Configuration

	ftm_config_t ftmInfo1, ftmInfo2, ftmInfo3;
	ftm_chnl_pwm_signal_param_t ftmParam1, ftmParam2, ftmParam3;
	ftm_pwm_level_select_t pwmLevel;

	//GPIO Configs ( Side buttons, Joystick button, Motor Dirs)

	gpio_pin_config_t sBtn_config,	joyBtn_config,	M1_D1_config,	M2_D1_config,	M3_D1_config;//

	// FTM QD Configs

	ftm_config_t ftmInfo;
	ftm_phase_params_t phaseParamsConfigStruct;
	unsigned int motor_cnt1;
	unsigned int motor_cnt2;

};

// Init functions
void RobotInterface_Init(RobotInterface * m);
void ADC_init(RobotInterface * m);
void GPIO_init(RobotInterface * m);
void PWM_init(RobotInterface * m);
void FTMQD_init(RobotInterface * m);

// State Functions
void ADC_read(RobotInterface * m);
void ReadSideBtns(RobotInterface * m);
void ReadJoyBtn(RobotInterface * m);
void ReadQDCounts(RobotInterface * m);
void UpdateState(RobotInterface * m);
unsigned int GetMotorCounter(RobotInterface * m, int motor_index);

void ProcessingCommand(RobotInterface * m); // cjun state

// Working Functions
void ManualDrive(RobotInterface * m);

// Debugging Function
void MotorTesting(RobotInterface * m);
void MotorTesting2(RobotInterface * m); // new DRV config
void ADC_Reading_Test(RobotInterface * m);
void PWM_test(RobotInterface * m); // outdated : do not use CJUN 12.07.2018


#endif /* ROBOTINTERFACE_H_ */
