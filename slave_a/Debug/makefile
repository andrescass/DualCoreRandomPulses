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
all: slave_a.axf

# Tool invocations
slave_a.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx_m0\Debug" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\src" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\Debug" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\inc" -L"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework" -Xlinker -Map="slave_a.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "slave_a_Debug.ld" -o "slave_a.axf" $(OBJS) $(USER_OBJS) $(LIBS) && arm-none-eabi-objcopy --target elf32-littlearm --verbose --strip-all --remove-section=.ARM.attributes --redefine-sym __vectors_start__=__vectors_start___core_m0app --keep-symbol __vectors_start___core_m0app --redefine-sym _data=__start_data_core_m0app --keep-symbol __start_data_core_m0app --redefine-sym _edata=__end_data_core_m0app --keep-symbol __end_data_core_m0app --remove-section=".bss*" --remove-section=".noinit*" --rename-section .ARM.exidx=".core_m0app.ARM.exidx" --rename-section .ARM.extab=".core_m0app.ARM.extab" --rename-section .text=".core_m0app" --rename-section .data=".core_m0app.data" "slave_a.axf" "slave_a.axf.o"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) slave_a.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "slave_a.axf"; # arm-none-eabi-objcopy -v -O binary "slave_a.axf" "slave_a.bin" ; # checksum -p LPC4337_M0 -d "slave_a.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
