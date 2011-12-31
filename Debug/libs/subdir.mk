################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/hash.c \
../libs/printfmt.c \
../libs/rand.c \
../libs/string.c 

OBJS += \
./libs/hash.o \
./libs/printfmt.o \
./libs/rand.o \
./libs/string.o 

C_DEPS += \
./libs/hash.d \
./libs/printfmt.d \
./libs/rand.d \
./libs/string.d 


# Each subdirectory must supply rules for building sources it contributes
libs/%.o: ../libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


