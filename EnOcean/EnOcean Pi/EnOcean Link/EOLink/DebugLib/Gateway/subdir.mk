################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Gateway/eoGateway.cpp 

OBJS += \
./Gateway/eoGateway.o 

CPP_DEPS += \
./Gateway/eoGateway.d 


# Each subdirectory must supply rules for building sources it contributes
Gateway/%.o: ../Gateway/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


