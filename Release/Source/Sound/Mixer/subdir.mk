################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/Mixer/Mixer.cpp 

OBJS += \
./Source/Sound/Mixer/Mixer.o 

CPP_DEPS += \
./Source/Sound/Mixer/Mixer.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/Mixer/%.o: ../Source/Sound/Mixer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


