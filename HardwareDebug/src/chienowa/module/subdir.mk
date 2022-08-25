################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/chienowa/module/b_module.c \
../src/chienowa/module/c_module.c \
../src/chienowa/module/e_module.c \
../src/chienowa/module/p_module.c \
../src/chienowa/module/s_module.c \
../src/chienowa/module/t_module.c 

COMPILER_OBJS += \
src/chienowa/module/b_module.obj \
src/chienowa/module/c_module.obj \
src/chienowa/module/e_module.obj \
src/chienowa/module/p_module.obj \
src/chienowa/module/s_module.obj \
src/chienowa/module/t_module.obj 

C_DEPS += \
src/chienowa/module/b_module.d \
src/chienowa/module/c_module.d \
src/chienowa/module/e_module.d \
src/chienowa/module/p_module.d \
src/chienowa/module/s_module.d \
src/chienowa/module/t_module.d 

# Each subdirectory must supply rules for building sources it contributes
src/chienowa/module/%.obj: ../src/chienowa/module/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\chienowa\module\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\chienowa\module\cDepSubCommand.tmp"
	ccrl -subcommand="src\chienowa\module\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\chienowa\module\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\chienowa\module\cSubCommand.tmp"
	ccrl -subcommand="src\chienowa\module\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

