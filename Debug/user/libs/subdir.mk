################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/libs/malloc.c \
../user/libs/panic.c \
../user/libs/stdio.c \
../user/libs/syscall.c \
../user/libs/thread.c \
../user/libs/ulib.c \
../user/libs/umain.c 

S_UPPER_SRCS += \
../user/libs/clone.S \
../user/libs/initcode.S 

OBJS += \
./user/libs/clone.o \
./user/libs/initcode.o \
./user/libs/malloc.o \
./user/libs/panic.o \
./user/libs/stdio.o \
./user/libs/syscall.o \
./user/libs/thread.o \
./user/libs/ulib.o \
./user/libs/umain.o 

C_DEPS += \
./user/libs/malloc.d \
./user/libs/panic.d \
./user/libs/stdio.d \
./user/libs/syscall.d \
./user/libs/thread.d \
./user/libs/ulib.d \
./user/libs/umain.d 


# Each subdirectory must supply rules for building sources it contributes
user/libs/%.o: ../user/libs/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

user/libs/%.o: ../user/libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


