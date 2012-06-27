################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RESTfulService.cpp \
../message.cpp \
../rest_server.cpp 

OBJS += \
./RESTfulService.o \
./message.o \
./rest_server.o 

CPP_DEPS += \
./RESTfulService.d \
./message.d \
./rest_server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/cores/arduino" -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/variants/mega" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Satelita1_RESTful" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


