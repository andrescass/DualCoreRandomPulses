################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Poisson.c \
../src/cr_startup_lpc43xx.c \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/Poisson.o \
./src/cr_startup_lpc43xx.o \
./src/crp.o \
./src/sysinit.o 

C_DEPS += \
./src/Poisson.d \
./src/cr_startup_lpc43xx.d \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M4 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC43XX__ -D__REDLIB__ -D__MULTICORE_NONE -I"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\LPC4337_Framework" -I"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\PoissonPulses\inc" -I"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\lpc_chip_43xx\inc" -I"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\lpc_chip_43xx\inc\usbd" -I"C:\Users\Crozzolo Marcos\Documents\81 -Repo_Sup\LPC4337\trunk\LPC4337_Framework\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


