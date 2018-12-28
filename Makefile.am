## Process this file with automake to produce Makefile.in

# Copyright (C) 2018-2018 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2018 Nicolas Boulenguez <nicolas@debian.org>

# Cache shared with autoconf.
ACLOCAL_AMFLAGS = -I m4

PACKAGE = libexadrums

# https://www.gnu.org/software/libtool/manual/libtool.html#Updating-version-info
exadrums_libtool_version_info = 0:0:0

# Distribute (in the tarball created by 'make dist-gzip').
EXTRA_DIST = LICENSE

# Distribute and install into docdir.
dist_doc_DATA = README.md

# Install into pkgconfigdir, but do not distribute.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = exadrums.pc

# Good habits.
AM_CXXFLAGS = -Wall
AM_LDFLAGS = -Wl,--as-needed

# Delegate library handling to libtool.
lib_LTLIBRARIES = libexadrums.la

libexadrums_la_CXXFLAGS = $(AM_CXXFLAGS) \
  -std=c++17 $(alsa_CFLAGS) $(tinyxml2_CFLAGS)
libexadrums_la_LDFLAGS = $(AM_LDFLAGS) \
  -version-info $(exadrums_libtool_version_info)
libexadrums_la_LIBADD = $(alsa_LIBS) $(tinyxml2_LIBS) -lpthread -lstdc++fs

# Distributed and embed into the library.
libexadrums_la_SOURCES = \
  Source/Api/Config/Config_api.cpp \
  Source/Api/Config/TriggerParameters_api.cpp \
  Source/Api/KitCreator/KitCreator_api.cpp \
  Source/Api/eXaDrums.cpp \
  Source/DrumKit/DrumModule/Module.cpp \
  Source/DrumKit/DrumModule/Module.h \
  Source/DrumKit/DrumModule/Recorder.cpp \
  Source/DrumKit/DrumModule/Recorder.h \
  Source/DrumKit/DrumModule/TrigSound.h \
  Source/DrumKit/Instruments/Cymbals/TestHiHat.cpp \
  Source/DrumKit/Instruments/Cymbals/TestHiHat.h \
  Source/DrumKit/Instruments/Drums/TestDrum.cpp \
  Source/DrumKit/Instruments/Drums/TestDrum.h \
  Source/DrumKit/Instruments/Instrument.cpp \
  Source/DrumKit/Instruments/Instrument.h \
  Source/DrumKit/Instruments/InstrumentFactory.h \
  Source/DrumKit/Instruments/InstrumentParameters.h \
  Source/DrumKit/Instruments/InstrumentSoundInfo.h \
  Source/DrumKit/Instruments/InstrumentType.h \
  Source/DrumKit/Instruments/Pads/Pad.cpp \
  Source/DrumKit/Instruments/Pads/Pad.h \
  Source/DrumKit/Kits/Kit.cpp \
  Source/DrumKit/Kits/Kit.h \
  Source/DrumKit/Kits/KitCreator.cpp \
  Source/DrumKit/Kits/KitManager.cpp \
  Source/DrumKit/Triggers/Curves/Curves.h \
  Source/DrumKit/Triggers/TriggerFactory.h \
  Source/DrumKit/Triggers/TriggerManager.cpp \
  Source/DrumKit/Triggers/TriggerState.h \
  Source/DrumKit/Triggers/Triggers/ContinuousTrigger.cpp \
  Source/DrumKit/Triggers/Triggers/ContinuousTrigger.h \
  Source/DrumKit/Triggers/Triggers/DiscreteTrigger.cpp \
  Source/DrumKit/Triggers/Triggers/DiscreteTrigger.h \
  Source/DrumKit/Triggers/Triggers/Trigger.cpp \
  Source/DrumKit/Triggers/Triggers/Trigger.h \
  Source/IO/HddSensor.cpp \
  Source/IO/HddSensor.h \
  Source/IO/ISensor.h \
  Source/IO/Serial.cpp \
  Source/IO/Serial.h \
  Source/IO/Spi.cpp \
  Source/IO/Spi.h \
  Source/IO/SpiSensor.cpp \
  Source/IO/SpiSensor.h \
  Source/Metronome/ClickTypes.h \
  Source/Metronome/Metronome.cpp \
  Source/Metronome/Metronome.h \
  Source/Metronome/MetronomeParameters.h \
  Source/Sound/Alsa/Alsa.cpp \
  Source/Sound/Alsa/Alsa.h \
  Source/Sound/Alsa/AlsaParameters.cpp \
  Source/Sound/Alsa/AlsaParameters.h \
  Source/Sound/Mixer/Mixer.cpp \
  Source/Sound/Mixer/Mixer.h \
  Source/Sound/Sound.cpp \
  Source/Sound/Sound.h \
  Source/Sound/SoundBank/SoundBank.cpp \
  Source/Sound/SoundBank/SoundBank.h \
  Source/Sound/SoundProcessor/SoundProcessor.cpp \
  Source/Sound/SoundProcessor/SoundProcessor.h \
  Source/Sound/SoundState.h \
  Source/Sound/Util/WavUtil.h \
  Source/Util/Crypt.h \
  Source/Util/Misc.h \
  Source/Util/Parsing.h \
  Source/Util/SimpleSafeQueue.h \
  Source/Util/Threading.h \
  Source/Util/Time.h

# Install into pkgincludedir, but do not distribute (it is generated
# by the configure.ac).
nodist_pkginclude_HEADERS = \
  Source/Api/eXaDrums.h

# Distribute and install into pkgincludedir.
pkginclude_HEADERS = \
  Source/Api/Config/AlsaParams_api.h \
  Source/Api/Config/Config_api.h \
  Source/Api/Config/Config_api.hpp \
  Source/Api/Config/TriggerParameters_api.h \
  Source/Api/KitCreator/KitCreator_api.h \
  Source/Api/KitCreator/KitCreator_api.hpp \
  Source/Api/eXaDrums.hpp \
  Source/DrumKit/Instruments/InstrumentParameters.h \
  Source/DrumKit/Instruments/InstrumentSoundInfo.h \
  Source/DrumKit/Instruments/InstrumentType.h \
  Source/DrumKit/Kits/KitCreator.h \
  Source/DrumKit/Kits/KitManager.h \
  Source/DrumKit/Kits/KitParameters.h \
  Source/DrumKit/Triggers/Curves/CurveType.h \
  Source/DrumKit/Triggers/TriggerLocation.h \
  Source/DrumKit/Triggers/TriggerManager.h \
  Source/DrumKit/Triggers/TriggerParameters.h \
  Source/DrumKit/Triggers/TriggerType.h \
  Source/IO/SensorType.h \
  Source/IO/SensorsConfig.h \
  Source/Sound/Alsa/AlsaParams.h \
  Source/Sound/InstrumentSoundType.h \
  Source/Util/Enums.h \
  Source/Util/Xml.h
