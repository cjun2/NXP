/*
 * The Clear BSD License
 * Copyright 2017-2018 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v4.1
processor: MKV31F512xxx12
package_id: MKV31F512VLL12
mcu_data: ksdk2_0
processor_version: 0.0.11
board: FRDM-KV31F
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
- name: BOARD_InitBUTTONsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitLEDsPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitDEBUG_UARTPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitACCELPeripheral
  id_prefix: BOARD_
  selectedCore: core0
- name: BOARD_InitTHERPeripheral
  id_prefix: BOARD_
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitBUTTONsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * SW3 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW3'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitBUTTONsPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SW3_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * SW2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'SW2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitBUTTONsPeripheral'
- peripheral: 'GPIOA'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTA_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_SW2_init(void) {
  /* Make sure, the clock gate for port A is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitLEDsPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LEDRGB_BLUE initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LEDRGB_BLUE'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTE_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LEDRGB_BLUE_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * LEDRGB_RED_GREEN initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LEDRGB_RED_GREEN'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitLEDsPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_LEDRGB_RED_GREEN_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitDEBUG_UARTPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DEBUG_UART initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DEBUG_UART'
- type: 'uart'
- mode: 'polling'
- type_id: 'uart_cd31a12aa8c79051fda42cc851a27c37'
- functional_group: 'BOARD_InitDEBUG_UARTPeripheral'
- peripheral: 'UART0'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
      - baudRate_Bps: '115200'
      - parityMode: 'kUART_ParityDisabled'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'false'
      - enableRx: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t BOARD_DEBUG_UART_config = {
  .baudRate_Bps = 115200,
  .parityMode = kUART_ParityDisabled,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 1,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = false,
  .enableRx = false
};

void BOARD_DEBUG_UART_init(void) {
  UART_Init(BOARD_DEBUG_UART_PERIPHERAL, &BOARD_DEBUG_UART_config, BOARD_DEBUG_UART_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * BOARD_InitACCELPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ACCEL_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t BOARD_ACCEL_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000,
  .glitchFilterWidth = 0
};

void BOARD_ACCEL_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(BOARD_ACCEL_I2C_PERIPHERAL, &BOARD_ACCEL_I2C_config, BOARD_ACCEL_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * ACCEL_INT2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_INT2'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_ACCEL_INT2_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * ACCEL_INT1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ACCEL_INT1'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_f970a92e447fa4793838db25a2947ed7'
- functional_group: 'BOARD_InitACCELPeripheral'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void BOARD_ACCEL_INT1_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * BOARD_InitTHERPeripheral functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * THERMOMETER initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'THERMOMETER'
- type: 'adc16'
- mode: 'ADC'
- type_id: 'adc16_7d827be2dc433dc756d94a7ce88cbcc5'
- functional_group: 'BOARD_InitTHERPeripheral'
- peripheral: 'ADC1'
- config_sets:
  - fsl_adc16:
    - adc16_config:
      - referenceVoltageSource: 'kADC16_ReferenceVoltageSourceVref'
      - clockSource: 'kADC16_ClockSourceAsynchronousClock'
      - enableAsynchronousClock: 'true'
      - clockDivider: 'kADC16_ClockDivider8'
      - resolution: 'kADC16_ResolutionSE12Bit'
      - longSampleMode: 'kADC16_LongSampleDisabled'
      - enableHighSpeed: 'false'
      - enableLowPower: 'false'
      - enableContinuousConversion: 'false'
    - adc16_channel_mux_mode: 'kADC16_ChannelMuxA'
    - adc16_hardware_compare_config:
      - hardwareCompareModeEnable: 'false'
    - doAutoCalibration: 'true'
    - trigger: 'false'
    - hardwareAverageConfiguration: 'kADC16_HardwareAverageDisabled'
    - enable_irq: 'false'
    - adc_interrupt:
      - IRQn: 'ADC1_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - adc16_channels_config:
      - 0:
        - enableDifferentialConversion: 'true'
        - channelNumber: 'DP.1'
        - channelNumber2: 'DM.1'
        - enableInterruptOnConversionCompleted: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
adc16_channel_config_t BOARD_THERMOMETER_channelsConfig[1] = {
  {
    .channelNumber = 1U,
    .enableDifferentialConversion = true,
    .enableInterruptOnConversionCompleted = false
  }
};
const adc16_config_t BOARD_THERMOMETER_config = {
  .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref,
  .clockSource = kADC16_ClockSourceAsynchronousClock,
  .enableAsynchronousClock = true,
  .clockDivider = kADC16_ClockDivider8,
  .resolution = kADC16_ResolutionSE12Bit,
  .longSampleMode = kADC16_LongSampleDisabled,
  .enableHighSpeed = false,
  .enableLowPower = false,
  .enableContinuousConversion = false
};
const adc16_channel_mux_mode_t BOARD_THERMOMETER_muxMode = kADC16_ChannelMuxA;
const adc16_hardware_average_mode_t BOARD_THERMOMETER_hardwareAverageMode = kADC16_HardwareAverageDisabled;

void BOARD_THERMOMETER_init(void) {
  /* Initialize ADC16 converter */
  ADC16_Init(BOARD_THERMOMETER_PERIPHERAL, &BOARD_THERMOMETER_config);
  /* Make sure, that software trigger is used */
  ADC16_EnableHardwareTrigger(BOARD_THERMOMETER_PERIPHERAL, false);
  /* Configure hardware average mode */
  ADC16_SetHardwareAverage(BOARD_THERMOMETER_PERIPHERAL, BOARD_THERMOMETER_hardwareAverageMode);
  /* Configure channel multiplexing mode */
  ADC16_SetChannelMuxMode(BOARD_THERMOMETER_PERIPHERAL, BOARD_THERMOMETER_muxMode);
  /* Perform auto calibration */
  ADC16_DoAutoCalibration(BOARD_THERMOMETER_PERIPHERAL);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
}

void BOARD_InitBUTTONsPeripheral(void)
{
  /* Initialize components */
  BOARD_SW3_init();
  BOARD_SW2_init();
}

void BOARD_InitLEDsPeripheral(void)
{
  /* Initialize components */
  BOARD_LEDRGB_BLUE_init();
  BOARD_LEDRGB_RED_GREEN_init();
}

void BOARD_InitDEBUG_UARTPeripheral(void)
{
  /* Initialize components */
  BOARD_DEBUG_UART_init();
}

void BOARD_InitACCELPeripheral(void)
{
  /* Initialize components */
  BOARD_ACCEL_I2C_init();
  BOARD_ACCEL_INT2_init();
  BOARD_ACCEL_INT1_init();
}

void BOARD_InitTHERPeripheral(void)
{
  /* Initialize components */
  BOARD_THERMOMETER_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
