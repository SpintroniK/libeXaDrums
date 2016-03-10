################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/IO/HddSensor.cpp \
../Source/IO/Serial.cpp \
../Source/IO/SpiSensor.cpp 

OBJS += \
./Source/IO/HddSensor.o \
./Source/IO/Serial.o \
./Source/IO/SpiSensor.o 

CPP_DEPS += \
./Source/IO/HddSensor.d \
./Source/IO/Serial.d \
./Source/IO/SpiSensor.d 


# Each subdirectory must supply rules for building sources it contributes
Source/IO/%.o: ../Source/IO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


