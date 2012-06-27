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
ArduinoUnderEclipse.lss \

FLASH_IMAGE += \
ArduinoUnderEclipse.hex \

EEPROM_IMAGE += \
ArduinoUnderEclipse.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ArduinoUnderEclipse.elf secondary-outputs

dependents:
	-cd /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Uno/Release && $(MAKE) clean all
	-cd /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release && $(MAKE) clean all
	-cd /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager/Release && $(MAKE) clean all

# Tool invocations
ArduinoUnderEclipse.elf: $(OBJS) $(USER_OBJS) /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Uno/Release/libArduino_Uno.a /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release/libArduino_Utils.a /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager/Release/libArduino_TaskManager.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Uno/Release" -L"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release" -L"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager/Release" -mmcu=atmega328p -o"ArduinoUnderEclipse.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

ArduinoUnderEclipse.lss: ArduinoUnderEclipse.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ArduinoUnderEclipse.elf  >"ArduinoUnderEclipse.lss"
	@echo 'Finished building: $@'
	@echo ' '

ArduinoUnderEclipse.hex: ArduinoUnderEclipse.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex ArduinoUnderEclipse.elf  "ArduinoUnderEclipse.hex"
	@echo 'Finished building: $@'
	@echo ' '

ArduinoUnderEclipse.eep: ArduinoUnderEclipse.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ArduinoUnderEclipse.elf  "ArduinoUnderEclipse.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ArduinoUnderEclipse.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t ArduinoUnderEclipse.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) ArduinoUnderEclipse.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Uno/Release/libArduino_Uno.a:
/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils/Release/libArduino_Utils.a:
/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager/Release/libArduino_TaskManager.a:

-include ../makefile.targets
