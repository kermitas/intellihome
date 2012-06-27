################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ArduinoUnderEclipse.cpp \
../CheckDallasDS18B20TemperatureRunnable.cpp \
../MemoryFree.cpp \
../OptexMX40PTCheckRunnable.cpp \
../_EEPROMData.cpp \
../_InternalEEPROM.cpp \
../_Led.cpp \
../_LedDotLoopTask.cpp \
../_LoopTaskInterface.cpp \
../_PrinterDebug.cpp \
../_PrinterSimple.cpp \
../_TimeATimeBTaskManagerTaskExecutionInfo.cpp \
../__InternalEEPROM.cpp \
../__InternalEEPROMDataToWrite.cpp \
../__InternalEEPROMIdDataOrganisation.cpp \
../__InternalEEPROMMemoryMapRecord.cpp \
../_ePIR.cpp \
../_ePIRCheckMotionDetectionRunnable.cpp \
../_ePirConfigureRunnable.cpp \
../_ePirOperationResult.cpp 

OBJS += \
./ArduinoUnderEclipse.o \
./CheckDallasDS18B20TemperatureRunnable.o \
./MemoryFree.o \
./OptexMX40PTCheckRunnable.o \
./_EEPROMData.o \
./_InternalEEPROM.o \
./_Led.o \
./_LedDotLoopTask.o \
./_LoopTaskInterface.o \
./_PrinterDebug.o \
./_PrinterSimple.o \
./_TimeATimeBTaskManagerTaskExecutionInfo.o \
./__InternalEEPROM.o \
./__InternalEEPROMDataToWrite.o \
./__InternalEEPROMIdDataOrganisation.o \
./__InternalEEPROMMemoryMapRecord.o \
./_ePIR.o \
./_ePIRCheckMotionDetectionRunnable.o \
./_ePirConfigureRunnable.o \
./_ePirOperationResult.o 

CPP_DEPS += \
./ArduinoUnderEclipse.d \
./CheckDallasDS18B20TemperatureRunnable.d \
./MemoryFree.d \
./OptexMX40PTCheckRunnable.d \
./_EEPROMData.d \
./_InternalEEPROM.d \
./_Led.d \
./_LedDotLoopTask.d \
./_LoopTaskInterface.d \
./_PrinterDebug.d \
./_PrinterSimple.d \
./_TimeATimeBTaskManagerTaskExecutionInfo.d \
./__InternalEEPROM.d \
./__InternalEEPROMDataToWrite.d \
./__InternalEEPROMIdDataOrganisation.d \
./__InternalEEPROMMemoryMapRecord.d \
./_ePIR.d \
./_ePIRCheckMotionDetectionRunnable.d \
./_ePirConfigureRunnable.d \
./_ePirOperationResult.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/cores/arduino" -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/variants/standard" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/ArduinoUnderEclipse" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


