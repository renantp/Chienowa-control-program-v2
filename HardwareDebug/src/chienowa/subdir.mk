################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/chienowa/adc.c \
../src/chienowa/circular_buffer.c \
../src/chienowa/crc8.c \
../src/chienowa/delay.c \
../src/chienowa/eeprom.c \
../src/chienowa/hand_sensor.c \
../src/chienowa/main.c \
../src/chienowa/raspberry_pi_communication.c \
../src/chienowa/runtime.c 

COMPILER_OBJS += \
src/chienowa/adc.obj \
src/chienowa/circular_buffer.obj \
src/chienowa/crc8.obj \
src/chienowa/delay.obj \
src/chienowa/eeprom.obj \
src/chienowa/hand_sensor.obj \
src/chienowa/main.obj \
src/chienowa/raspberry_pi_communication.obj \
src/chienowa/runtime.obj 

C_DEPS += \
src/chienowa/adc.d \
src/chienowa/circular_buffer.d \
src/chienowa/crc8.d \
src/chienowa/delay.d \
src/chienowa/eeprom.d \
src/chienowa/hand_sensor.d \
src/chienowa/main.d \
src/chienowa/raspberry_pi_communication.d \
src/chienowa/runtime.d 

# Each subdirectory must supply rules for building sources it contributes
src/chienowa/%.obj: ../src/chienowa/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\chienowa\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\chienowa\cDepSubCommand.tmp"
	ccrl -subcommand="src\chienowa\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\chienowa\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\chienowa\cSubCommand.tmp"
	ccrl -subcommand="src\chienowa\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

