################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc43xx-m0app.c \
../src/ipc_msg.c \
../src/slave_a.c \
../src/sysinit.c 

OBJS += \
./src/cr_startup_lpc43xx-m0app.o \
./src/ipc_msg.o \
./src/slave_a.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_startup_lpc43xx-m0app.d \
./src/ipc_msg.d \
./src/slave_a.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC43XX__ -D__REDLIB__ -D__MULTICORE_M0APP -DCORE_M0APP -I"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx_m0\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\slave_a\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx_m0\inc\config_m0app" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx_m0\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


