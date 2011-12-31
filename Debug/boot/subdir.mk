################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../boot/bootmain.c 

S_UPPER_SRCS += \
../boot/bootasm.S 

OBJS += \
./boot/bootasm.o \
./boot/bootmain.o 

C_DEPS += \
./boot/bootmain.d 


# Each subdirectory must supply rules for building sources it contributes
boot/%.o: ../boot/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

boot/%.o: ../boot/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


