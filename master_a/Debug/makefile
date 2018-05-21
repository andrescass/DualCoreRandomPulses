################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: master_a.axf

# Tool invocations
master_a.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx\Debug" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\src" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\Debug" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\inc" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework" -Xlinker -Map="master_a.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "master_a_Debug.ld" -o "master_a.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) master_a.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "master_a.axf"; # arm-none-eabi-objcopy -v -O binary "master_a.axf" "master_a.bin" ; # checksum -p LPC4337 -d "master_a.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
