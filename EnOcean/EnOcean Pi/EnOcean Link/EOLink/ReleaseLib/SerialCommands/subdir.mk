################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SerialCommands/eoSerialCommand.cpp 

OBJS += \
./SerialCommands/eoSerialCommand.o 

CPP_DEPS += \
./SerialCommands/eoSerialCommand.d 


# Each subdirectory must supply rules for building sources it contributes
SerialCommands/%.o: ../SerialCommands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


