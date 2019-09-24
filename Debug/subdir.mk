################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP.c \
../CPU_sleep.c \
../DIO_operations.c \
../LCD.c \
../OS.c \
../OS_PBCfg.c \
../Timer0_function.c \
../infotainment.c \
../keypad.c 

OBJS += \
./APP.o \
./CPU_sleep.o \
./DIO_operations.o \
./LCD.o \
./OS.o \
./OS_PBCfg.o \
./Timer0_function.o \
./infotainment.o \
./keypad.o 

C_DEPS += \
./APP.d \
./CPU_sleep.d \
./DIO_operations.d \
./LCD.d \
./OS.d \
./OS_PBCfg.d \
./Timer0_function.d \
./infotainment.d \
./keypad.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


