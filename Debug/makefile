################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include user/subdir.mk
-include user/libs/subdir.mk
-include tools/subdir.mk
-include obj/user/subdir.mk
-include obj/user/libs/subdir.mk
-include obj/sign/tools/subdir.mk
-include obj/libs/subdir.mk
-include obj/subdir.mk
-include obj/kern/trap/subdir.mk
-include obj/kern/syscall/subdir.mk
-include obj/kern/sync/subdir.mk
-include obj/kern/schedule/subdir.mk
-include obj/kern/process/subdir.mk
-include obj/kern/mm/subdir.mk
-include obj/kern/libs/subdir.mk
-include obj/kern/init/subdir.mk
-include obj/kern/fs/subdir.mk
-include obj/kern/driver/subdir.mk
-include obj/kern/debug/subdir.mk
-include obj/boot/subdir.mk
-include libs/subdir.mk
-include kern/trap/subdir.mk
-include kern/syscall/subdir.mk
-include kern/sync/subdir.mk
-include kern/schedule/subdir.mk
-include kern/process/subdir.mk
-include kern/mm/subdir.mk
-include kern/libs/subdir.mk
-include kern/init/subdir.mk
-include kern/fs/subdir.mk
-include kern/driver/subdir.mk
-include kern/debug/subdir.mk
-include boot/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ucore

# Tool invocations
ucore: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"ucore" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ucore
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
