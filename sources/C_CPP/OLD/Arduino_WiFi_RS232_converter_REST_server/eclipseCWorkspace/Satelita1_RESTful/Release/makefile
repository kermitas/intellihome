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
libSatelita1_RESTful.lss \

FLASH_IMAGE += \
libSatelita1_RESTful.hex \

EEPROM_IMAGE += \
libSatelita1_RESTful.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: libSatelita1_RESTful.a secondary-outputs

dependents:
	-cd /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Mega_2560_or_Mega_ADK/Release && $(MAKE) all

# Tool invocations
libSatelita1_RESTful.a: $(OBJS) /home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Mega_2560_or_Mega_ADK/Release/libArduino_Mega_2560_or_Mega_ADK.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libSatelita1_RESTful.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libSatelita1_RESTful.lss: libSatelita1_RESTful.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libSatelita1_RESTful.a  >"libSatelita1_RESTful.lss"
	@echo 'Finished building: $@'
	@echo ' '

libSatelita1_RESTful.hex: libSatelita1_RESTful.a
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex libSatelita1_RESTful.a  "libSatelita1_RESTful.hex"
	@echo 'Finished building: $@'
	@echo ' '

libSatelita1_RESTful.eep: libSatelita1_RESTful.a
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex libSatelita1_RESTful.a  "libSatelita1_RESTful.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libSatelita1_RESTful.a
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t libSatelita1_RESTful.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(ARCHIVES)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) libSatelita1_RESTful.a
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Mega_2560_or_Mega_ADK/Release/libArduino_Mega_2560_or_Mega_ADK.a:

-include ../makefile.targets
