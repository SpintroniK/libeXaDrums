################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/SoundProcessor/Curves/Curves.cpp 

OBJS += \
./Source/Sound/SoundProcessor/Curves/Curves.o 

CPP_DEPS += \
./Source/Sound/SoundProcessor/Curves/Curves.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/SoundProcessor/Curves/%.o: ../Source/Sound/SoundProcessor/Curves/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


