################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Message/eoAbstractMessage.cpp \
../Message/eoMessage.cpp \
../Message/eoTelegram.cpp 

OBJS += \
./Message/eoAbstractMessage.o \
./Message/eoMessage.o \
./Message/eoTelegram.o 

CPP_DEPS += \
./Message/eoAbstractMessage.d \
./Message/eoMessage.d \
./Message/eoTelegram.d 


# Each subdirectory must supply rules for building sources it contributes
Message/%.o: ../Message/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


