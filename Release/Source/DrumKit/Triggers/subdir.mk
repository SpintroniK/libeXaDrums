################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Triggers/TriggerLocation.cpp \
../Source/DrumKit/Triggers/TriggerManager.cpp 

OBJS += \
./Source/DrumKit/Triggers/TriggerLocation.o \
./Source/DrumKit/Triggers/TriggerManager.o 

CPP_DEPS += \
./Source/DrumKit/Triggers/TriggerLocation.d \
./Source/DrumKit/Triggers/TriggerManager.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Triggers/%.o: ../Source/DrumKit/Triggers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


