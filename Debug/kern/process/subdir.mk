################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kern/process/proc.c 

S_UPPER_SRCS += \
../kern/process/entry.S \
../kern/process/switch.S 

OBJS += \
./kern/process/entry.o \
./kern/process/proc.o \
./kern/process/switch.o 

C_DEPS += \
./kern/process/proc.d 


# Each subdirectory must supply rules for building sources it contributes
kern/process/%.o: ../kern/process/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kern/process/%.o: ../kern/process/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


