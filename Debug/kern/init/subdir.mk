################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kern/init/init.c 

S_UPPER_SRCS += \
../kern/init/entry.S 

OBJS += \
./kern/init/entry.o \
./kern/init/init.o 

C_DEPS += \
./kern/init/init.d 


# Each subdirectory must supply rules for building sources it contributes
kern/init/%.o: ../kern/init/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kern/init/%.o: ../kern/init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


