################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TPG_2.c \
../src/cr_startup_lpc43xx.c \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/TPG_2.o \
./src/cr_startup_lpc43xx.o \
./src/crp.o \
./src/sysinit.o 

C_DEPS += \
./src/TPG_2.d \
./src/cr_startup_lpc43xx.d \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__MULTICORE_NONE -DNDEBUG -D__CODE_RED -DCORE_M4 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC43XX__ -D__REDLIB__ -I"C:\Users\Invap\Documents\Firmware\Marcos\LPC4337_Framework" -I"C:\Users\Invap\Documents\Firmware\Marcos\TPG_2\inc" -I"C:\Users\Invap\Documents\Firmware\Marcos\lpc_chip_43xx\inc" -I"C:\Users\Invap\Documents\Firmware\Marcos\lpc_chip_43xx\inc\usbd" -I"C:\Users\Invap\Documents\Firmware\Marcos\LPC4337_Framework\inc" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


