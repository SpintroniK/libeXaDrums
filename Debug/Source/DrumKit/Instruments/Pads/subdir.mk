################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Instruments/Pads/Pad.cpp 

OBJS += \
./Source/DrumKit/Instruments/Pads/Pad.o 

CPP_DEPS += \
./Source/DrumKit/Instruments/Pads/Pad.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Instruments/Pads/%.o: ../Source/DrumKit/Instruments/Pads/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


