/*
 * RobotInterface.c
 *
 *  Created on: Nov 29, 2018
 *      Author: Changhan
 */

#include "RobotInterface.h"

void RobotInterface_Init(RobotInterface * m)
{
	for (int i=0;i<2;i++)
	{
		m->ADC_data[i]=0; // reading value from Joysticks 0 - 4096
		m->sbtn[i]=0;	// reading value from Side buttons 0-1

	}

	m->joybtn = 0;
	m->ADC_init = 0 ,	m->PWM_init=0 ,	m->GPIO_init=0;

	ADC_init(m);
	PWM_init(m);
	GPIO_init(m);
	FTMQD_init(m);
}

void ADC_init(RobotInterface * m)
{
	ADC16_GetDefaultConfig(&m->adc16ConfigStruct);

#ifdef BOARD_ADC_USE_ALT_VREF
	m->adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif

    ADC16_Init(DEMO_ADC16_BASE, &m->adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false); /* Make sure the software trigger is used. */
    ADC16_SetChannelMuxMode(DEMO_ADC16_BASE, kADC16_ChannelMuxB);
    #if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION


		    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASE))
		    {
		        //PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
		    }
		    else
		    {
		        //PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
		    }

		    m->adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
		    m->adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

		    m->adc16ChannelConfigStruct2.channelNumber = DEMO_ADC16_USER_CHANNEL2;
		    m->adc16ChannelConfigStruct2.enableInterruptOnConversionCompleted = false;

		#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
		    m->adc16ChannelConfigStruct.enableDifferentialConversion = false;
		    m->adc16ChannelConfigStruct2.enableDifferentialConversion = false;

		    m->ADC_init = 1; // WHEN DONE adc INIT FLAG UP
#endif
		#endif
}

void ADC_read(RobotInterface * m)
{
	ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &m->adc16ChannelConfigStruct);

			while (0U == (kADC16_ChannelConversionDoneFlag &
						  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
			{
			}
			m->ADC_data[0]=ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);
	ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &m->adc16ChannelConfigStruct2);

	while (0U == (kADC16_ChannelConversionDoneFlag &
				  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
	{
	}
	m->ADC_data[1]=ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);

}

void PWM_init(RobotInterface * m)
{

	/* Configure ftm params with frequency 24kHZ */
		m->pwmLevel = kFTM_HighTrue;
		m->ftmParam1.chnlNumber = BOARD_FTM_CHANNEL1;
		m->ftmParam1.level = m->pwmLevel;
		m->ftmParam1.dutyCyclePercent = 1U;
		m->ftmParam1.firstEdgeDelayPercent = 0U;

		m->ftmParam2.chnlNumber = BOARD_FTM_CHANNEL2;
		m->ftmParam2.level = m->pwmLevel;
		m->ftmParam2.dutyCyclePercent = 1U;
		m->ftmParam2.firstEdgeDelayPercent = 0U;

		m->ftmParam3.chnlNumber = BOARD_FTM_CHANNEL3;
		m->ftmParam3.level = m->pwmLevel;
		m->ftmParam3.dutyCyclePercent = 1U;
		m->ftmParam3.firstEdgeDelayPercent = 0U;


	    FTM_GetDefaultConfig(&m->ftmInfo1);
	    FTM_GetDefaultConfig(&m->ftmInfo2);
	    FTM_GetDefaultConfig(&m->ftmInfo3);
	    /* Initialize FTM module */

	    FTM_Init(BOARD_FTM_BASEADDR1, &m->ftmInfo1);
	    FTM_Init(BOARD_FTM_BASEADDR2, &m->ftmInfo2);
	    FTM_Init(BOARD_FTM_BASEADDR3, &m->ftmInfo3);

	    FTM_SetupPwm(BOARD_FTM_BASEADDR1, &m->ftmParam1, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);
	    FTM_SetupPwm(BOARD_FTM_BASEADDR2, &m->ftmParam2, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);
	    FTM_SetupPwm(BOARD_FTM_BASEADDR3, &m->ftmParam3, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);

	    FTM_StartTimer(BOARD_FTM_BASEADDR1, kFTM_SystemClock);
	    FTM_StartTimer(BOARD_FTM_BASEADDR2, kFTM_SystemClock);
	    FTM_StartTimer(BOARD_FTM_BASEADDR3, kFTM_SystemClock);

	    m->PWM_init =1;

}
void GPIO_init(RobotInterface * m)
{
	// Side buttons
	m->sBtn_config.pinDirection = kGPIO_DigitalInput;
	m->sBtn_config.outputLogic = 0;
	// Joy stick button
	m->joyBtn_config.pinDirection = kGPIO_DigitalInput;
	m->joyBtn_config.outputLogic = 0;
	// motor direction

	m->M1_D1_config.pinDirection =kGPIO_DigitalOutput;
	m->M1_D1_config.outputLogic = 0;

	m->M2_D1_config.pinDirection =kGPIO_DigitalOutput;
	m->M2_D1_config.outputLogic = 0;

	m->M3_D1_config.pinDirection =kGPIO_DigitalOutput;
	m->M3_D1_config.outputLogic = 0;



	//M1,2,3=================================================================
	GPIO_PinInit(Board_GPIO_DIR_M1,Board_DIR_M1_1, &m->M1_D1_config);

	GPIO_PinInit(Board_GPIO_DIR_M2,Board_DIR_M2_1, &m->M2_D1_config);

	GPIO_PinInit(Board_GPIO_DIR_M3,Board_DIR_M3_1, &m->M3_D1_config);

	// Side Buttons
	PORT_SetPinInterruptConfig(SBTN_Port_base, SideBtn1_Pin, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(SBTN_Port_base, SideBtn2_Pin, kPORT_InterruptFallingEdge);

	GPIO_PinInit(SBTN_Board_base, SideBtn1_Pin, &m->sBtn_config);
	GPIO_PinInit(SBTN_Board_base, SideBtn2_Pin, &m->sBtn_config);

	// joystick select
	GPIO_PinInit(JOYBTN_Board_base, JoyBtn_Pin, &m->joyBtn_config);

}
void FTMQD_init(RobotInterface * m)
{
	/* Motor 1 QD Encoder ******************************************************
	 *
	Manual implementation with FTM interrupts is required (if need)

	**************************************************************************/
	FTM_GetDefaultConfig(&m->ftmInfo);
    m->ftmInfo.prescale = kFTM_Prescale_Divide_1;

    /* Motor 2 QD Encoder******************************************************/
    FTM_Init(M1_FTM_BASEADDR, &m->ftmInfo);
    /* Set the modulo values for Quad Decoder. */
    FTM_SetQuadDecoderModuloValue(M1_FTM_BASEADDR, 0U, QUAD_DECODER_MODULO);
    /* Enable the Quad Decoder mode. */
    m->phaseParamsConfigStruct.enablePhaseFilter = true;
    m->phaseParamsConfigStruct.phaseFilterVal = 16;
    m->phaseParamsConfigStruct.phasePolarity = kFTM_QuadPhaseNormal;
    FTM_SetupQuadDecode(M1_FTM_BASEADDR, &m->phaseParamsConfigStruct, /* Phase A. */
                        &m->phaseParamsConfigStruct,                    /* Phase B. */
                        kFTM_QuadPhaseEncode);
    FTM_ClearQuadDecoderCounterValue(M1_FTM_BASEADDR);

    /* Motor 3 QD Encoder ******************************************************/
	FTM_Init(M2_FTM_BASEADDR, &m->ftmInfo);
	/* Set the modulo values for Quad Decoder. */
	FTM_SetQuadDecoderModuloValue(M2_FTM_BASEADDR, 0U, QUAD_DECODER_MODULO);
	/* Enable the Quad Decoder mode. */
	m->phaseParamsConfigStruct.enablePhaseFilter = true;
	m->phaseParamsConfigStruct.phaseFilterVal = 16;
	m->phaseParamsConfigStruct.phasePolarity = kFTM_QuadPhaseNormal;
	FTM_SetupQuadDecode(M2_FTM_BASEADDR, &m->phaseParamsConfigStruct, /* Phase A. */
						&m->phaseParamsConfigStruct,                    /* Phase B. */
						kFTM_QuadPhaseEncode);
	FTM_ClearQuadDecoderCounterValue(M2_FTM_BASEADDR);

	 m->motor_cnt1= 0U;
	 m->motor_cnt2= 0U;

}
void ReadSideBtns(RobotInterface * m)
{
	m->sbtn[0]=GPIO_ReadPinInput(SBTN_Board_base, SideBtn1_Pin);
	m->sbtn[1]=GPIO_ReadPinInput(SBTN_Board_base, SideBtn2_Pin);
}
void ReadJoyBtn(RobotInterface * m)
{
	m->joybtn=GPIO_ReadPinInput(JOYBTN_Board_base, JoyBtn_Pin);
}
void ReadQDCounts(RobotInterface * m)
{
	m->motor_cnt1=FTM_GetQuadDecoderCounterValue(M1_FTM_BASEADDR);
	m->motor_cnt2=FTM_GetQuadDecoderCounterValue(M2_FTM_BASEADDR);
}
unsigned int GetMotorCounter(RobotInterface * m, int motor_index)
{
	// index should be 1,2

	if (motor_index ==1)
	{
		return m->motor_cnt1;
	}
	if (motor_index ==2)
	{
		return m->motor_cnt2;
	}
	return 0;
}
void UpdateState(RobotInterface * m)
{
	ADC_read(m);
	ReadSideBtns(m);
	ReadJoyBtn(m);
	ReadQDCounts(m);
}
void MotorTesting(RobotInterface * m)
{
	// M1, M2 is driven by ADC M3 will be driven by Btn command
	// DRV8834 with 1 dir configuration
		unsigned int Sig1, Sig2, Sig3;
		int ADC_max = 4000;
		int ADC_min = 20;
		int ADC_mid =2048;
		int ADC_zero_tol = 30;


//M1
		if (m->ADC_data[0] >=ADC_mid+ADC_zero_tol)
			{
				// CW
				Sig1=(unsigned int)(((double)(m->ADC_data[0]-ADC_max)/ADC_max)*99);
				//PRINTF("sig2 %d \r\n",Sig2);
				GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,0);
					}
			if(m->ADC_data[0] <ADC_mid-ADC_zero_tol)
			{	//CCW
				Sig1=(unsigned int)(((double)(ADC_max-m->ADC_data[0])/ADC_max)*99);
				GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);

			}
			if(m->ADC_data[0] >=(ADC_mid-ADC_zero_tol) && m->ADC_data[0] <(ADC_mid+ADC_zero_tol))
			{
				Sig1=0;
				GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);
			}

			// M2

			if (m->ADC_data[0] >=ADC_mid+ADC_zero_tol)
			{
				// CW
				Sig2=(unsigned int)(((double)(m->ADC_data[1]-ADC_max)/ADC_max)*99);
				//PRINTF("sig3 %d \r\n",Sig3);
				GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,0);
			}
			if(m->ADC_data[0] <ADC_mid-ADC_zero_tol)
			{	//CCW
				Sig2=(unsigned int)(((double)(ADC_max-m->ADC_data[1])/ADC_max)*99);
				GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
			}
			if(m->ADC_data[0] >=(ADC_mid-ADC_zero_tol) && m->ADC_data[0] <(ADC_mid+ADC_zero_tol))
			{
				Sig2=0;
				GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
			}

	 // Motor3 by SBtn1,2


			if (m->sbtn[0]==1 && m->sbtn[1]==0)
			{
				GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,0);
				Sig3=99U;
			}
			if (m->sbtn[0]==0 && m->sbtn[1] ==1)
			{
				GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
				Sig3=99U;
			}
			if (m->sbtn[0]==0 && m->sbtn[1]==0)
			{

				GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
				Sig3=0U;
			}
			if (m->sbtn[0]==1 && m->sbtn[1]==1)
			{

				GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
				Sig1=0U;
			}

			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, 0U);
			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, 0U);
			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, 0U);
			/* Update PWM duty cycle */
			FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, kFTM_CenterAlignedPwm, (Sig1));

			FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, kFTM_CenterAlignedPwm, (Sig2));

			FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, kFTM_CenterAlignedPwm, (Sig3));

			/* Software trigger to update registers */
			FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR1, true);

			FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR2, true);

			FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR3, true);

			/* Start channel output with updated dutycycle */
			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, m->pwmLevel);

			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, m->pwmLevel);

			FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, m->pwmLevel);//CJUN

			//printf("sig3 %d \r\n",Sig3);

}
void ManualDrive(RobotInterface * m)
{
	/*
	// M1/2 is driven by ADC M3 will be driven by Btn command
	unsigned int Sig1, Sig2, Sig3;


	if (m->ADC_data[0] >=2100)
	{
		// CW
		Sig1=(unsigned int)(((double)(m->ADC_data[0]-2048)/2048)*99);
		//PRINTF("sig2 %d \r\n",Sig2);
		GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,0);
	}
	if(m->ADC_data[0] <2000)
	{	//CCW
		Sig1=(unsigned int)(((double)(2048-m->ADC_data[0])/2048)*99);
		GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);
	}
	if(m->ADC_data[0] >=2000 && m->ADC_data[0] <2100)
	{
		Sig1=0;
		GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);
	}

	// M2

	if (m->ADC_data[1] >=2100)
	{
		// CW
		Sig2=(unsigned int)(((double)(m->ADC_data[1]-2048)/2048)*99);
		PRINTF("dir m3 is  %d \r\n",0);
		GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,0);
	}
	if(m->ADC_data[1] <2000)
	{	//CCW
		PRINTF("dir m3 is  %d \r\n",1);
		Sig2=(unsigned int)(((double)(2048-m->ADC_data[1])/2048)*99);
		GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);

	}
	if(m->ADC_data[1] >=2000 && m->ADC_data[1] <2100)
	{
		Sig2=0;
		GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
		PRINTF("dir m3 is  %d \r\n",1);
	}
// Motor3 by SBtn1,2


	if (m->sbtn[0]==1 && m->sbtn[1]==0)
	{
		GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,0);
		Sig3=99U;
	}
	if (m->sbtn[0]==0 && m->sbtn[1] ==1)
	{
		GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
		Sig3=99U;
	}
	if (m->sbtn[0]==0 && m->sbtn[1]==0)
	{

		GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
		Sig3=0U;
	}
	if (m->sbtn[0]==1 && m->sbtn[1]==1)
	{

		GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
		Sig3=0U;
	}

	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, 0U);
	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, 0U);
	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, 0U);
	// Update PWM duty cycle
	FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, kFTM_CenterAlignedPwm, (Sig1));

	FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, kFTM_CenterAlignedPwm, (Sig2));

	FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, kFTM_CenterAlignedPwm, (Sig3));

	// Software trigger to update registers
	FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR1, true);

	FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR2, true);

	FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR3, true);

	// Start channel output with updated dutycycle
	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, m->pwmLevel);

	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, m->pwmLevel);

	FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, m->pwmLevel);//CJUN
	*/
}

void ADC_Reading_Test(RobotInterface * m)
{
	printf("ADC 1 is : %d \n",m->ADC_data[0]);
	printf("ADC 2 is : %d \n",m->ADC_data[1]);
	printf("Side Btn 1 is : %d \n",m->sbtn[0]);
	printf("Side Btn 2 is : %d \n",m->sbtn[1]);


}
void PWM_test(RobotInterface * m)
{
	// M2 is driven by ADC M3 will be driven by Btn command
		unsigned int Sig1, Sig2, Sig3;


		if (m->ADC_data[0] >=2100)
		{
			// CW
			Sig2=(unsigned int)(((double)(m->ADC_data[0]-2048)/2048)*99);
			//PRINTF("sig2 %d \r\n",Sig2);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,0);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_2,1);
		}
		if(m->ADC_data[0] <2000)
		{	//CCW
			Sig2=(unsigned int)(((double)(2048-m->ADC_data[0])/2048)*99);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_2,0);
		}
		if(m->ADC_data[0] >=2000 && m->ADC_data[0] <2100)
		{
			Sig2=0;
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_2,1);
		}

		// M3

		if (m->ADC_data[1] >=2100)
		{
			// CW
			Sig3=(unsigned int)(((double)(m->ADC_data[1]-2048)/2048)*99);
			//PRINTF("sig3 %d \r\n",Sig3);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,0);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_2,1);
		}
		if(m->ADC_data[1] <2000)
		{	//CCW
			Sig3=(unsigned int)(((double)(2048-m->ADC_data[1])/2048)*99);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_2,0);
		}
		if(m->ADC_data[1] >=2000 && m->ADC_data[1] <2100)
		{
			Sig3=0;
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
		//	GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_2,1);
		}
	// Motor1 by SBtn1,2


		if (m->sbtn[0]==1 && m->sbtn[1]==0)
		{

			Sig1=99U;
		}
		if (m->sbtn[0]==0 && m->sbtn[1] ==1)
		{

			Sig1=99U;
		}
		if (m->sbtn[0]==0 && m->sbtn[1]==0)
		{


			Sig1=0U;
		}
		if (m->sbtn[0]==1 && m->sbtn[1]==1)
		{


			Sig1=0U;
		}

		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, 0U);
		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, 0U);
		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, 0U);
		/* Update PWM duty cycle */
		FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, kFTM_CenterAlignedPwm, (Sig1));

		FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, kFTM_CenterAlignedPwm, (Sig2));

		FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, kFTM_CenterAlignedPwm, (Sig3));

		/* Software trigger to update registers */
		FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR1, true);

		FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR2, true);

		FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR3, true);

		/* Start channel output with updated dutycycle */
		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, m->pwmLevel);

		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, m->pwmLevel);

		FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, m->pwmLevel);//CJUN
}
void MotorTesting2(RobotInterface * m)
{
	// M1, M2 is driven by ADC M3 will be driven by Btn command
		// DRV8834 with 2 dir configuration

			unsigned int Sig1, Sig2, Sig3;
			int ADC_max = 4000;
			int ADC_min = 20;
			int ADC_mid =2048;
			int ADC_zero_tol = 30;


	//M1
			if (m->ADC_data[0] >=ADC_mid+ADC_zero_tol)
				{
					// CW
					Sig1=(unsigned int)(((double)(m->ADC_data[0]-ADC_max)/ADC_max)*99);
					GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M1,Board_DIR_M1_2,0);
						}
				if(m->ADC_data[0] <ADC_mid-ADC_zero_tol)
				{	//CCW
					Sig1=(unsigned int)(((double)(ADC_max-m->ADC_data[0])/ADC_max)*99);
					GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,0);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M1,Board_DIR_M1_2,1);

				}
				if(m->ADC_data[0] >=(ADC_mid-ADC_zero_tol) && m->ADC_data[0] <(ADC_mid+ADC_zero_tol))
				{
					Sig1=0;
					GPIO_WritePinOutput(Board_GPIO_DIR_M1,Board_DIR_M1_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M1,Board_DIR_M1_2,1);
				}

				// M2

				if (m->ADC_data[0] >=ADC_mid+ADC_zero_tol)
				{
					// CW
					Sig2=(unsigned int)(((double)(m->ADC_data[1]-ADC_max)/ADC_max)*99);
					//PRINTF("sig3 %d \r\n",Sig3);
					GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M2,Board_DIR_M2_2,0);
				}
				if(m->ADC_data[0] <ADC_mid-ADC_zero_tol)
				{	//CCW
					Sig2=(unsigned int)(((double)(ADC_max-m->ADC_data[1])/ADC_max)*99);
					GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,0);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M2,Board_DIR_M2_2,1);
				}
				if(m->ADC_data[0] >=(ADC_mid-ADC_zero_tol) && m->ADC_data[0] <(ADC_mid+ADC_zero_tol))
				{
					Sig2=0;
					GPIO_WritePinOutput(Board_GPIO_DIR_M2,Board_DIR_M2_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M2,Board_DIR_M2_2,1);
				}

		 // Motor3 by SBtn1,2


				if (m->sbtn[0]==1 && m->sbtn[1]==0)
				{
					GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M3,Board_DIR_M3_2,0);
					Sig3=99U;
				}
				if (m->sbtn[0]==0 && m->sbtn[1] ==1)
				{
					GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,0);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M3,Board_DIR_M3_2,1);
					Sig3=99U;
				}
				if (m->sbtn[0]==0 && m->sbtn[1]==0)
				{

					GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,0);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M3,Board_DIR_M3_2,0);
					Sig3=0U;
				}
				if (m->sbtn[0]==1 && m->sbtn[1]==1)
				{

					GPIO_WritePinOutput(Board_GPIO_DIR_M3,Board_DIR_M3_1,1);
					GPIO_WritePinOutput(Board_GPIO_DIR2_M3,Board_DIR_M3_2,1);
					Sig1=0U;
				}

				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, 0U);
				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, 0U);
				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, 0U);
				/* Update PWM duty cycle */
				FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, kFTM_CenterAlignedPwm, (Sig1));

				FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, kFTM_CenterAlignedPwm, (Sig2));

				FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, kFTM_CenterAlignedPwm, (Sig3));

				/* Software trigger to update registers */
				FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR1, true);

				FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR2, true);

				FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR3, true);

				/* Start channel output with updated dutycycle */
				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR1, BOARD_FTM_CHANNEL1, m->pwmLevel);

				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR2, BOARD_FTM_CHANNEL2, m->pwmLevel);

				FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR3, BOARD_FTM_CHANNEL3, m->pwmLevel);//CJUN

				//printf("sig3 %d \r\n",Sig3);
}
void ProcessingCommand(RobotInterface * m)
{
	/*
#define ROBOT_MCUOFF	-11
#define ROBOT_OFF	-10
#define ROBOT_STOP	-1
#define ROBOT_READY 0
#define ROBOT_MOVE	1
#define ROBOT_HOME	2*/
	STATE this = m->m_state;
	switch(this.command)
	{
		case ROBOT_MCUOFF: switch(this.status){
									case ROBOT_MCUOFF: 	return;
									case ROBOT_OFF:		return;
									case ROBOT_STOP:	return;
									case ROBOT_READY:	return;
									case ROBOT_MOVE:	return;
											}
		case ROBOT_OFF: switch(this.status){
									case ROBOT_MCUOFF: 	return;
									case ROBOT_OFF:		return;
									case ROBOT_STOP:	return;
									case ROBOT_READY:	return;
									case ROBOT_MOVE:	return;
													}
		case ROBOT_STOP: switch(this.status){
									case ROBOT_MCUOFF: 	return;
									case ROBOT_OFF:		return;
									case ROBOT_STOP:	return;
									case ROBOT_READY:	return;
									case ROBOT_MOVE:	return;
													}
		case ROBOT_READY: switch(this.status){
									case ROBOT_MCUOFF: 	return;
									case ROBOT_OFF:		return;
									case ROBOT_STOP:	return;
									case ROBOT_READY:	return;
									case ROBOT_MOVE:	return;
													}
		case ROBOT_MOVE: switch(this.status){
									case ROBOT_MCUOFF: 	return;
									case ROBOT_OFF:		return;
									case ROBOT_STOP:	return;
									case ROBOT_READY:	return;
									case ROBOT_MOVE:	return;
													}
	}
}
