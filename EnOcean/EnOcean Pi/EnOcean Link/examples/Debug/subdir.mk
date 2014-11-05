################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GatewayFiltered_example.cpp \
../Gateway_example.cpp \
../PTM_example.cpp \
../commands_example.cpp \
../deviceManager_example.cpp \
../linuxPacketStream_example.cpp \
../packetStream_example.cpp \
../profile_examples.cpp \
../sandbox.cpp \
../sendTelegram_example.cpp \
../storage_example.cpp 

OBJS += \
./GatewayFiltered_example.o \
./Gateway_example.o \
./PTM_example.o \
./commands_example.o \
./deviceManager_example.o \
./linuxPacketStream_example.o \
./packetStream_example.o \
./profile_examples.o \
./sandbox.o \
./sendTelegram_example.o \
./storage_example.o 

CPP_DEPS += \
./GatewayFiltered_example.d \
./Gateway_example.d \
./PTM_example.d \
./commands_example.d \
./deviceManager_example.d \
./linuxPacketStream_example.d \
./packetStream_example.d \
./profile_examples.d \
./sandbox.d \
./sendTelegram_example.d \
./storage_example.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../../EOLink" -I../../EOLink/Includes -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


