################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/KitManager/KitManager.cpp 

OBJS += \
./Source/DrumKit/KitManager/KitManager.o 

CPP_DEPS += \
./Source/DrumKit/KitManager/KitManager.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/KitManager/%.o: ../Source/DrumKit/KitManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


