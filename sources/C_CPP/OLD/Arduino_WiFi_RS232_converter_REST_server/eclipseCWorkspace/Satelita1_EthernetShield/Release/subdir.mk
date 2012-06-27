################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Dhcp.cpp \
../Dns.cpp \
../Ethernet.cpp \
../EthernetClient.cpp \
../EthernetServer.cpp \
../EthernetUdp.cpp \
../SPI.cpp \
../socket.cpp \
../w5100.cpp 

OBJS += \
./Dhcp.o \
./Dns.o \
./Ethernet.o \
./EthernetClient.o \
./EthernetServer.o \
./EthernetUdp.o \
./SPI.o \
./socket.o \
./w5100.o 

CPP_DEPS += \
./Dhcp.d \
./Dns.d \
./Ethernet.d \
./EthernetClient.d \
./EthernetServer.d \
./EthernetUdp.d \
./SPI.d \
./socket.d \
./w5100.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/cores/arduino" -I"/home/as/Pobrane/PROGRAMOWANIE/arduino-1.0/hardware/arduino/variants/mega" -D__IN_ECLIPSE__=1 -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


