################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Api/Config/Config_api.cpp \
../Source/Api/Config/TriggerParameters_api.cpp 

OBJS += \
./Source/Api/Config/Config_api.o \
./Source/Api/Config/TriggerParameters_api.o 

CPP_DEPS += \
./Source/Api/Config/Config_api.d \
./Source/Api/Config/TriggerParameters_api.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Api/Config/%.o: ../Source/Api/Config/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


