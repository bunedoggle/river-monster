################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Packet/eoLinuxPacketStream.cpp \
../Packet/eoPacket.cpp \
../Packet/eoPacketStream.cpp 

OBJS += \
./Packet/eoLinuxPacketStream.o \
./Packet/eoPacket.o \
./Packet/eoPacketStream.o 

CPP_DEPS += \
./Packet/eoLinuxPacketStream.d \
./Packet/eoPacket.d \
./Packet/eoPacketStream.d 


# Each subdirectory must supply rules for building sources it contributes
Packet/%.o: ../Packet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


