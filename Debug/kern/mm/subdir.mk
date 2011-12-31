################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kern/mm/buddy_pmm.c \
../kern/mm/pmm.c \
../kern/mm/shmem.c \
../kern/mm/slab.c \
../kern/mm/swap.c \
../kern/mm/vmm.c 

OBJS += \
./kern/mm/buddy_pmm.o \
./kern/mm/pmm.o \
./kern/mm/shmem.o \
./kern/mm/slab.o \
./kern/mm/swap.o \
./kern/mm/vmm.o 

C_DEPS += \
./kern/mm/buddy_pmm.d \
./kern/mm/pmm.d \
./kern/mm/shmem.d \
./kern/mm/slab.d \
./kern/mm/swap.d \
./kern/mm/vmm.d 


# Each subdirectory must supply rules for building sources it contributes
kern/mm/%.o: ../kern/mm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


