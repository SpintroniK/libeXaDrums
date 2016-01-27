################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Trigger.cpp 

OBJS += \
./Source/DrumKit/Trigger.o 

CPP_DEPS += \
./Source/DrumKit/Trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/%.o: ../Source/DrumKit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


