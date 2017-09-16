################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Triggers/Curves/Curves.cpp 

OBJS += \
./Source/DrumKit/Triggers/Curves/Curves.o 

CPP_DEPS += \
./Source/DrumKit/Triggers/Curves/Curves.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Triggers/Curves/%.o: ../Source/DrumKit/Triggers/Curves/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


