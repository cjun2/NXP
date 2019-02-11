################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DC_Motor.c \
../source/RobotInterface.c \
../source/SR70_MC.c \
../source/semihost_hardfault.c 

OBJS += \
./source/DC_Motor.o \
./source/RobotInterface.o \
./source/SR70_MC.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/DC_Motor.d \
./source/RobotInterface.d \
./source/SR70_MC.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKV31F512VLL12_cm4 -DCPU_MKV31F512VLL12 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DFRDM_KV31F -DFREEDOM -DFSL_RTOS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../startup -I../utilities -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/portable -I../amazon-freertos/include -I../board/src -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


