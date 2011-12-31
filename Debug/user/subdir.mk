################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/badarg.c \
../user/badbrktest.c \
../user/badsegment.c \
../user/brkfreetest.c \
../user/brktest.c \
../user/buggy_wait.c \
../user/buggy_wait2.c \
../user/cowtest.c \
../user/divzero.c \
../user/exit.c \
../user/faultread.c \
../user/faultreadkernel.c \
../user/forktest.c \
../user/forktree.c \
../user/hello.c \
../user/jenny.c \
../user/matrix.c \
../user/mmaptest.c \
../user/pgdir.c \
../user/primer.c \
../user/shmemtest.c \
../user/sleep.c \
../user/sleepkill.c \
../user/softint.c \
../user/spin.c \
../user/swaptest.c \
../user/testbss.c \
../user/threadfork.c \
../user/threadgroup1.c \
../user/threadgroup2.c \
../user/threadtest.c \
../user/threadwork.c \
../user/waitkill.c \
../user/yield.c 

OBJS += \
./user/badarg.o \
./user/badbrktest.o \
./user/badsegment.o \
./user/brkfreetest.o \
./user/brktest.o \
./user/buggy_wait.o \
./user/buggy_wait2.o \
./user/cowtest.o \
./user/divzero.o \
./user/exit.o \
./user/faultread.o \
./user/faultreadkernel.o \
./user/forktest.o \
./user/forktree.o \
./user/hello.o \
./user/jenny.o \
./user/matrix.o \
./user/mmaptest.o \
./user/pgdir.o \
./user/primer.o \
./user/shmemtest.o \
./user/sleep.o \
./user/sleepkill.o \
./user/softint.o \
./user/spin.o \
./user/swaptest.o \
./user/testbss.o \
./user/threadfork.o \
./user/threadgroup1.o \
./user/threadgroup2.o \
./user/threadtest.o \
./user/threadwork.o \
./user/waitkill.o \
./user/yield.o 

C_DEPS += \
./user/badarg.d \
./user/badbrktest.d \
./user/badsegment.d \
./user/brkfreetest.d \
./user/brktest.d \
./user/buggy_wait.d \
./user/buggy_wait2.d \
./user/cowtest.d \
./user/divzero.d \
./user/exit.d \
./user/faultread.d \
./user/faultreadkernel.d \
./user/forktest.d \
./user/forktree.d \
./user/hello.d \
./user/jenny.d \
./user/matrix.d \
./user/mmaptest.d \
./user/pgdir.d \
./user/primer.d \
./user/shmemtest.d \
./user/sleep.d \
./user/sleepkill.d \
./user/softint.d \
./user/spin.d \
./user/swaptest.d \
./user/testbss.d \
./user/threadfork.d \
./user/threadgroup1.d \
./user/threadgroup2.d \
./user/threadtest.d \
./user/threadwork.d \
./user/waitkill.d \
./user/yield.d 


# Each subdirectory must supply rules for building sources it contributes
user/%.o: ../user/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


