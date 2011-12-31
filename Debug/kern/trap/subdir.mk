################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kern/trap/trap.c 

S_UPPER_SRCS += \
../kern/trap/trapentry.S \
../kern/trap/vectors.S 

OBJS += \
./kern/trap/trap.o \
./kern/trap/trapentry.o \
./kern/trap/vectors.o 

C_DEPS += \
./kern/trap/trap.d 


# Each subdirectory must supply rules for building sources it contributes
kern/trap/%.o: ../kern/trap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kern/trap/%.o: ../kern/trap/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


