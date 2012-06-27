################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DallasTemperature.cpp \
../File.cpp \
../MemoryFree.cpp \
../OneWire.cpp \
../PinHighLowRunnable.cpp \
../Runnable.cpp \
../SD.cpp \
../Sd2Card.cpp \
../SdFile.cpp \
../SdVolume.cpp 

OBJS += \
./DallasTemperature.o \
./File.o \
./MemoryFree.o \
./OneWire.o \
./PinHighLowRunnable.o \
./Runnable.o \
./SD.o \
./Sd2Card.o \
./SdFile.o \
./SdVolume.o 

CPP_DEPS += \
./DallasTemperature.d \
./File.d \
./MemoryFree.d \
./OneWire.d \
./PinHighLowRunnable.d \
./Runnable.d \
./SD.d \
./Sd2Card.d \
./SdFile.d \
./SdVolume.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/cores/arduino" -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/variants/standard" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


