################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Kits/Kit.cpp \
../Source/DrumKit/Kits/KitManager.cpp 

OBJS += \
./Source/DrumKit/Kits/Kit.o \
./Source/DrumKit/Kits/KitManager.o 

CPP_DEPS += \
./Source/DrumKit/Kits/Kit.d \
./Source/DrumKit/Kits/KitManager.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Kits/%.o: ../Source/DrumKit/Kits/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


