################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/SoundBank/SoundBank.cpp 

OBJS += \
./Source/Sound/SoundBank/SoundBank.o 

CPP_DEPS += \
./Source/Sound/SoundBank/SoundBank.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/SoundBank/%.o: ../Source/Sound/SoundBank/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


