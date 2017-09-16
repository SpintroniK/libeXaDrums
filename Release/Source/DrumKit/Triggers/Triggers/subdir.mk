################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Triggers/Triggers/ContinuousTrigger.cpp \
../Source/DrumKit/Triggers/Triggers/DiscreteTrigger.cpp \
../Source/DrumKit/Triggers/Triggers/Trigger.cpp 

OBJS += \
./Source/DrumKit/Triggers/Triggers/ContinuousTrigger.o \
./Source/DrumKit/Triggers/Triggers/DiscreteTrigger.o \
./Source/DrumKit/Triggers/Triggers/Trigger.o 

CPP_DEPS += \
./Source/DrumKit/Triggers/Triggers/ContinuousTrigger.d \
./Source/DrumKit/Triggers/Triggers/DiscreteTrigger.d \
./Source/DrumKit/Triggers/Triggers/Trigger.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Triggers/Triggers/%.o: ../Source/DrumKit/Triggers/Triggers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


