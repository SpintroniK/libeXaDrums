################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DrumKit/Instruments/Cymbal.cpp \
../Source/DrumKit/Instruments/Drum.cpp \
../Source/DrumKit/Instruments/Instrument.cpp 

OBJS += \
./Source/DrumKit/Instruments/Cymbal.o \
./Source/DrumKit/Instruments/Drum.o \
./Source/DrumKit/Instruments/Instrument.o 

CPP_DEPS += \
./Source/DrumKit/Instruments/Cymbal.d \
./Source/DrumKit/Instruments/Drum.d \
./Source/DrumKit/Instruments/Instrument.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DrumKit/Instruments/%.o: ../Source/DrumKit/Instruments/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

