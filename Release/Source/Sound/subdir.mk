################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/Mixer.cpp \
../Source/Sound/SoundSample.cpp 

OBJS += \
./Source/Sound/Mixer.o \
./Source/Sound/SoundSample.o 

CPP_DEPS += \
./Source/Sound/Mixer.d \
./Source/Sound/SoundSample.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/%.o: ../Source/Sound/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


