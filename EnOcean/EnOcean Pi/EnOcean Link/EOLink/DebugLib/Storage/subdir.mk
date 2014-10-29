################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Storage/eoArchive.cpp \
../Storage/eoArchiveTXT.cpp \
../Storage/eoHeader.cpp \
../Storage/eoISerialize.cpp \
../Storage/eoStorageManager.cpp 

OBJS += \
./Storage/eoArchive.o \
./Storage/eoArchiveTXT.o \
./Storage/eoHeader.o \
./Storage/eoISerialize.o \
./Storage/eoStorageManager.o 

CPP_DEPS += \
./Storage/eoArchive.d \
./Storage/eoArchiveTXT.d \
./Storage/eoHeader.d \
./Storage/eoISerialize.d \
./Storage/eoStorageManager.d 


# Each subdirectory must supply rules for building sources it contributes
Storage/%.o: ../Storage/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../Includes" -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


