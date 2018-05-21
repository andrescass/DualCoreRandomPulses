################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_start_m0.c \
../src/cr_startup_lpc43xx.c \
../src/crp.c \
../src/ipc_msg.c \
../src/master_a.c \
../src/sysinit.c 

OBJS += \
./src/cr_start_m0.o \
./src/cr_startup_lpc43xx.o \
./src/crp.o \
./src/ipc_msg.o \
./src/master_a.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_start_m0.d \
./src/cr_startup_lpc43xx.d \
./src/crp.d \
./src/ipc_msg.d \
./src/master_a.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M4 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC43XX__ -D__REDLIB__ -DLPC43_MULTICORE_M0APP -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0APP -I"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\master_a\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\LPC4337_Framework\inc" -I"C:\Work\Supervisores\multicore\LPC4337\trunk\lpc_chip_43xx\inc\usbd" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


