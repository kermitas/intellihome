################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Arduino_TaskManager.cpp \
../TaskManager.cpp \
../TaskManagerMemoryConfigurator.cpp \
../TaskManagerRecord.cpp \
../TaskManagerScheduler.cpp \
../TaskManagerSchedulerAndOr.cpp \
../TaskManagerSchedulerOneAfterOne.cpp \
../TaskManagerSchedulerOneExecution.cpp \
../TaskManagerSchedulerTimeIntervals.cpp \
../TaskManagerStatistics.cpp \
../TaskManagerStatisticsBasic.cpp 

OBJS += \
./Arduino_TaskManager.o \
./TaskManager.o \
./TaskManagerMemoryConfigurator.o \
./TaskManagerRecord.o \
./TaskManagerScheduler.o \
./TaskManagerSchedulerAndOr.o \
./TaskManagerSchedulerOneAfterOne.o \
./TaskManagerSchedulerOneExecution.o \
./TaskManagerSchedulerTimeIntervals.o \
./TaskManagerStatistics.o \
./TaskManagerStatisticsBasic.o 

CPP_DEPS += \
./Arduino_TaskManager.d \
./TaskManager.d \
./TaskManagerMemoryConfigurator.d \
./TaskManagerRecord.d \
./TaskManagerScheduler.d \
./TaskManagerSchedulerAndOr.d \
./TaskManagerSchedulerOneAfterOne.d \
./TaskManagerSchedulerOneExecution.d \
./TaskManagerSchedulerTimeIntervals.d \
./TaskManagerStatistics.d \
./TaskManagerStatisticsBasic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/cores/arduino" -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/variants/standard" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_TaskManager" -I"/home/as/Pobrane/PROGRAMOWANIE/eclipseCWorkspace/Arduino_Utils" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


