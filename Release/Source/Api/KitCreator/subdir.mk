################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Api/KitCreator/KitCreator_api.cpp 

OBJS += \
./Source/Api/KitCreator/KitCreator_api.o 

CPP_DEPS += \
./Source/Api/KitCreator/KitCreator_api.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Api/KitCreator/%.o: ../Source/Api/KitCreator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


