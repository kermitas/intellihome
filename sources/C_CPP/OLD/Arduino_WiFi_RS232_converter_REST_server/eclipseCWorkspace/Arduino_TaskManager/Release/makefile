################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
libArduino_TaskManager.lss \

FLASH_IMAGE += \
libArduino_TaskManager.hex \

EEPROM_IMAGE += \
libArduino_TaskManager.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: libArduino_TaskManager.a secondary-outputs

dependents:
	-cd /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release && $(MAKE) clean all

# Tool invocations
libArduino_TaskManager.a: $(OBJS) /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release/libArduino_Utils.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libArduino_TaskManager.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libArduino_TaskManager.lss: libArduino_TaskManager.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libArduino_TaskManager.a  >"libArduino_TaskManager.lss"
	@echo 'Finished building: $@'
	@echo ' '

libArduino_TaskManager.hex: libArduino_TaskManager.a
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex libArduino_TaskManager.a  "libArduino_TaskManager.hex"
	@echo 'Finished building: $@'
	@echo ' '

libArduino_TaskManager.eep: libArduino_TaskManager.a
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex libArduino_TaskManager.a  "libArduino_TaskManager.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libArduino_TaskManager.a
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t libArduino_TaskManager.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(ARCHIVES)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) libArduino_TaskManager.a
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release/libArduino_Utils.a:

-include ../makefile.targets
