################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Triggers/DrumTrigger.cpp \
../Source/DrumKit/Triggers/Trigger.cpp 

OBJS += \
./Source/DrumKit/Triggers/DrumTrigger.o \
./Source/DrumKit/Triggers/Trigger.o 

CPP_DEPS += \
./Source/DrumKit/Triggers/DrumTrigger.d \
./Source/DrumKit/Triggers/Trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Triggers/%.o: ../Source/DrumKit/Triggers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


