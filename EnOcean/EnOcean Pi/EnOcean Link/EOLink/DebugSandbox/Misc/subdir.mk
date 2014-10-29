################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Misc/eoConverter.cpp \
../Misc/eoDebug.cpp \
../Misc/eoProc.cpp 

OBJS += \
./Misc/eoConverter.o \
./Misc/eoDebug.o \
./Misc/eoProc.o 

CPP_DEPS += \
./Misc/eoConverter.d \
./Misc/eoDebug.d \
./Misc/eoProc.d 


# Each subdirectory must supply rules for building sources it contributes
Misc/%.o: ../Misc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


