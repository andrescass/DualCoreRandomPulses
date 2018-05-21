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
all: PoissonPulses.axf

dependents:
	-cd C:/Users/Crozzolo\ Marcos/Documents/81\ -Repo_Sup/LPC4337/trunk/LPC4337_Framework/Debug && $(MAKE) all

# Tool invocations
PoissonPulses.axf: $(OBJS) $(USER_OBJS) C:/Users/Crozzolo\ Marcos/Documents/81\ -Repo_Sup/LPC4337/trunk/LPC4337_Framework/Debug/libLPC4337_Framework.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\LPC4337_Framework\Debug" -L"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\lpc_chip_43xx\Debug" -Xlinker -Map="PoissonPulses.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "TPG_2_Debug.ld" -o "PoissonPulses.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) PoissonPulses.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "PoissonPulses.axf"; # arm-none-eabi-objcopy -v -O binary "PoissonPulses.axf" "PoissonPulses.bin" ; # checksum -p LPC4337 -d "PoissonPulses.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/Crozzolo\ Marcos/Documents/81\ -Repo_Sup/LPC4337/trunk/LPC4337_Framework/Debug/libLPC4337_Framework.a:

-include ../makefile.targets
