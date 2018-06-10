################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/Sound/SoundProcessor/subdir.mk
-include Source/Sound/SoundBank/subdir.mk
-include Source/Sound/Mixer/subdir.mk
-include Source/Sound/Alsa/subdir.mk
-include Source/Sound/subdir.mk
-include Source/Metronome/subdir.mk
-include Source/IO/subdir.mk
-include Source/DrumKit/Triggers/Triggers/subdir.mk
-include Source/DrumKit/Triggers/Curves/subdir.mk
-include Source/DrumKit/Triggers/subdir.mk
-include Source/DrumKit/Kits/subdir.mk
-include Source/DrumKit/Instruments/Pads/subdir.mk
-include Source/DrumKit/Instruments/Drums/subdir.mk
-include Source/DrumKit/Instruments/Cymbals/subdir.mk
-include Source/DrumKit/Instruments/subdir.mk
-include Source/DrumKit/DrumModule/subdir.mk
-include Source/Api/KitCreator/subdir.mk
-include Source/Api/Config/subdir.mk
-include Source/Api/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libexadrums.so.0

# Tool invocations
libexadrums.so.0: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -o "libexadrums.so.0" $(OBJS) $(USER_OBJS) $(LIBS) -shared -Wl,-soname=libexadrums.so.0
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(LIBRARIES)$(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) libexadrums.so.0
	-@echo ' '

post-build:
	-ln -sf libexadrums.so.0 libexadrums.so
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
