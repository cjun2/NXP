/*
 * RobotInterface.h
 *
 *  Created on: Nov 29, 2018
 *      Author: Changhan Jun
 */

#ifndef ROBOTINTERFACE_H_
#define ROBOTINTERFACE_H_



#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
/*
#include "fsl_adc16.h"
#include "board.h"
#include "fsl_ftm.h"
#include "fsl_port.h"
#include "fsl_gpio.h"*/

#include "ADC_driver.h" // includes ADC definitions
#include "GPIOs_driver.h" // includes GPIOs definitions
#include <PWM_driver.h> // includes FTM (PWM) definitions
#include <FTM_QD_driver.h> // include FTM QD definitions

#define n_motors 3U


// Sys Config:
#define	d_nAXES			3	// Number of Axes
#define	d_nDI			3	// Number of Digital Inputs
#define	d_nDI_LimM		6	// Number of Digital Inputs assigned to Negative Limit Switches
#define	d_nDO			2	// Number of Digital Outputs

// Frequencies:
#define	d_wdFreq		8	// [Hz]
#define	d_dlgFreq		5	// [Hz]
#define	d_nSoftOK		4	// Number of times watchdog may run faster than dialogue timer. [10]

// Watch Dog Thread States and Commands:
#define	WD_STOP			-2
#define	WD_OFF			-1
#define	WD_GET			0
#define	WD_ON			1

// Robot states and commands:

#define	ROBOT_OFF		-10	//
#define	ROBOT_STOP		-1
#define	ROBOT_READY		0
#define	ROBOT_MOVE		1
#define	ROBOT_HOME		2

// Home Switch Type:
#define HOME_NO			0	// Any position
#define HOME_HARD		1	// Hard limit
#define HOME_SWITCH		2	// Limit switch

typedef struct STR_STATE STR_STATE;
typedef struct STR_COORD STR_COORD;
typedef struct STR_INI STR_INI;

struct		STR_STATE {	long	cycle;
						//SYSTEMTIME	time;
						short	status, command;
						const char * statusTxt, *errorTxt, *messageTxt, *log;
						bool	di[d_nDI], hardLimM[d_nAXES], softLimM[d_nAXES], softLimP[d_nAXES], stall[d_nAXES];
						int		eFlags[d_nAXES];
						bool	moving;};
struct		STR_COORD {	double	step[d_nAXES], joint[d_nAXES], robot[d_nAXES], encoderCnt[d_nAXES], stepperCnt[d_nAXES];	// Motor Steps, Joint coordinate [mm], Robot space coordinate {Entrance and Target};
						float	stepErr[d_nAXES], stepVel[d_nAXES], stepDrive[d_nAXES];};	//
struct		STR_INI	{	double	Kp[d_nAXES], Ki[d_nAXES], Kd[d_nAXES], Kv[d_nAXES], Ka[d_nAXES], Kpv[d_nAXES], Kiv[d_nAXES], Kvf[d_nAXES];
						double	saturation[d_nAXES], softLimM[d_nAXES], softLimP[d_nAXES];};



// Types of Motion commands and parameters:
#define	MOV_INDIVIDUAL_ABSOLUTE		0
#define	MOV_INDIVIDUAL_RELATIVE		1
#define	MOV_COORDINATED_ABSOLUTE	2
#define	MOV_COORDINATED_RELATIVE	3
typedef struct STR_MOVE STR_MOVE;
struct		STR_MOVE {	short type; // joystick:1 Position:2
						int dir[d_nAXES]; // -1 0 1
						int vel[d_nAXES]; // 0-99U
						uint32_t target[d_nAXES]; // +-sizeof(uint32_t)
						};

typedef struct RobotInterface RobotInterface;

struct RobotInterface {
	// UI- Input state
	int ADC_data[2]; // reading value from Joysticks 0 - 4096
	int sbtn[2];	// reading value from Side buttons 0-1
	int joybtn;
	bool ADC_init,	PWM_init,	GPIO_init;
	/*
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

	*/
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

	// State and command variables
	STR_STATE		m_state;
	STR_INI			m_ini, m_ini0;
	STR_COORD		m_coord;
	STR_MOVE		m_movPar;



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

// State Machine
void WatchdogThread(RobotInterface * m_robot);
void UpdateRead(RobotInterface * m);
void UpdateStatus(RobotInterface * m);
void UpdateCommand(RobotInterface * m);
void ProcessCommand(RobotInterface * m_robot);
bool MotionExecution(RobotInterface * m_robot);
void HomeAxes_StartThread(RobotInterface * m_robot); // Homing Thread


// RTOS

void vContinuousProcessingTask(void *pvParameters);

#endif /* ROBOTINTERFACE_H_ */
