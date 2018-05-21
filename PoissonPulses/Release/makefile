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
all: TPG_2.axf

dependents:
	-cd C:/Users/Invap/Documents/Firmware/Marcos/LPC4337_Framework/Release && $(MAKE) clean all

# Tool invocations
TPG_2.axf: $(OBJS) $(USER_OBJS) C:/Users/Invap/Documents/Firmware/Marcos/LPC4337_Framework/Release/libLPC4337_Framework.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Invap\Documents\Firmware\Marcos\LPC4337_Framework\Release" -L"C:\Users\Invap\Documents\Firmware\Marcos\lpc_chip_43xx\Release" -Xlinker -Map="TPG_2.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "TPG_2_Release.ld" -o "TPG_2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) TPG_2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TPG_2.axf"; # arm-none-eabi-objcopy -v -O binary "TPG_2.axf" "TPG_2.bin" ; # checksum -p LPC4337 -d "TPG_2.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/Invap/Documents/Firmware/Marcos/LPC4337_Framework/Release/libLPC4337_Framework.a:

-include ../makefile.targets
