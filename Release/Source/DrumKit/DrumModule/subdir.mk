################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/DrumModule/Module.cpp \
../Source/DrumKit/DrumModule/Recorder.cpp 

OBJS += \
./Source/DrumKit/DrumModule/Module.o \
./Source/DrumKit/DrumModule/Recorder.o 

CPP_DEPS += \
./Source/DrumKit/DrumModule/Module.d \
./Source/DrumKit/DrumModule/Recorder.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/DrumModule/%.o: ../Source/DrumKit/DrumModule/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


