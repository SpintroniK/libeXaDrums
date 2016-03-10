################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Api/eXaDrums.cpp 

OBJS += \
./Source/Api/eXaDrums.o 

CPP_DEPS += \
./Source/Api/eXaDrums.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Api/%.o: ../Source/Api/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


