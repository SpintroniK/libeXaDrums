################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/SoundProcessor/SoundProcessor.cpp 

OBJS += \
./Source/Sound/SoundProcessor/SoundProcessor.o 

CPP_DEPS += \
./Source/Sound/SoundProcessor/SoundProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/SoundProcessor/%.o: ../Source/Sound/SoundProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


