################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: V15_02\ SR70_HL_Controller_state.axf

# Tool invocations
V15_02\ SR70_HL_Controller_state.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="V15_02 SR70_HL_Controller_state.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T SR70_mcu_debug_v2_Debug.ld -o "V15_02 SR70_HL_Controller_state.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) "V15_02 SR70_HL_Controller_state.axf"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "V15_02 SR70_HL_Controller_state.axf"; # arm-none-eabi-objcopy -v -O binary "V15_02 SR70_HL_Controller_state.axf" "V15_02 SR70_HL_Controller_state.bin" ; # checksum -p MKV31F512xxx12 -d "V15_02 SR70_HL_Controller_state.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
