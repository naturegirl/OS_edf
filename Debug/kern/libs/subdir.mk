################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kern/libs/rb_tree.c \
../kern/libs/readline.c \
../kern/libs/stdio.c 

OBJS += \
./kern/libs/rb_tree.o \
./kern/libs/readline.o \
./kern/libs/stdio.o 

C_DEPS += \
./kern/libs/rb_tree.d \
./kern/libs/readline.d \
./kern/libs/stdio.d 


# Each subdirectory must supply rules for building sources it contributes
kern/libs/%.o: ../kern/libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


