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

#define n_motors 3U


typedef struct RobotInterface RobotInterface;

struct RobotInterface {
	// UI- Input state
	int ADC_data[2]; // reading value from Joysticks 0 - 4096
	int sbtn[2];	// reading value from Side buttons 0-1
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

	gpio_pin_config_t sBtn_config,	joyBtn_config;//	M1_D1_config,	M2_D1_config,	M3_D1_config;//
	gpio_pin_config_t motor_drv_DI, motor_drv_DO;
	// FTM QD Configs

	ftm_config_t ftmInfo;
	ftm_phase_params_t phaseParamsConfigStruct;
	// Motor Control variables =====================
	int32_t motor_counts[n_motors];
	int32_t old_motor_counts[n_motors];
	float motor_rpm[n_motors];
	double cnt_per_turn;
		// Position Control variables
	bool Pos_PID_enable[n_motors];
	float ki[n_motors],kd[n_motors],kp[n_motors];
	int32_t target[n_motors]; // [deg]
	int32_t error[n_motors], derror[n_motors], olderror[n_motors], Ierror[n_motors];
};

// Init functions
void RobotInterface_Init(RobotInterface * m);
void ADC_init(RobotInterface * m);
void GPIO_init(RobotInterface * m);
void PWM_init(RobotInterface * m);
void FTMQD_init(RobotInterface * m);
void SetLimits(RobotInterface * m);
// State Functions
void ADC_read(RobotInterface * m);
void ReadSideBtns(RobotInterface * m);
void ReadJoyBtn(RobotInterface * m);

void ReadQDCountsPractical(RobotInterface * m);
void UpdateRPM(RobotInterface * m, uint32_t delT);
float GetRPM(RobotInterface * m_robot, int index);
void UpdateState(RobotInterface * m);

int32_t GetMotorABSCounter(RobotInterface * m, int motor_index);

// Debugging Function
void ADC_Reading_Test(RobotInterface * m);


// Control Options

	// Pos PID Functions
void enablePosMode(RobotInterface * m_robot, int index[3]);
void disablePosMode(RobotInterface * m_robot,int index[3]);
void MotorPathPlanning(RobotInterface * m_robot);
void SetTarget(RobotInterface * m_robot, int32_t target[3]);
void MotorPositionControl(RobotInterface * m_robot,uint32_t delT); // position controller, followed by target updates
	//	Manual Command

void MotorLifeCycleRunning(RobotInterface * m_robot);
void MotorCommand(RobotInterface * m,int dir[3], int Sigs[3]); // for now only for M1/M2

#endif /* ROBOTINTERFACE_H_ */
