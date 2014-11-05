################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TeachIn/eoTeachInModule.cpp 

OBJS += \
./TeachIn/eoTeachInModule.o 

CPP_DEPS += \
./TeachIn/eoTeachInModule.d 


# Each subdirectory must supply rules for building sources it contributes
TeachIn/%.o: ../TeachIn/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


