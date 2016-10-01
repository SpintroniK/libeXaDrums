################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Instruments/Instrument.cpp \
../Source/DrumKit/Instruments/InstrumentType.cpp 

OBJS += \
./Source/DrumKit/Instruments/Instrument.o \
./Source/DrumKit/Instruments/InstrumentType.o 

CPP_DEPS += \
./Source/DrumKit/Instruments/Instrument.d \
./Source/DrumKit/Instruments/InstrumentType.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Instruments/%.o: ../Source/DrumKit/Instruments/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


