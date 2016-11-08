################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Instruments/Cymbals/TestHiHat.cpp 

OBJS += \
./Source/DrumKit/Instruments/Cymbals/TestHiHat.o 

CPP_DEPS += \
./Source/DrumKit/Instruments/Cymbals/TestHiHat.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Instruments/Cymbals/%.o: ../Source/DrumKit/Instruments/Cymbals/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


