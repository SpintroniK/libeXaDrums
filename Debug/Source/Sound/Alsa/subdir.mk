################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Sound/Alsa/Alsa.cpp 

OBJS += \
./Source/Sound/Alsa/Alsa.o 

CPP_DEPS += \
./Source/Sound/Alsa/Alsa.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sound/Alsa/%.o: ../Source/Sound/Alsa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


