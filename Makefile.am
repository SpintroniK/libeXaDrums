## Process this file with automake to produce Makefile.in

# Copyright (C) 2018-2019 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2019 Nicolas Boulenguez <nicolas@debian.org>

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
AM_LDFLAGS = -Wl,--as-needed -Wl,--no-undefined

# Delegate library handling to libtool.
lib_LTLIBRARIES = libexadrums.la

libexadrums_la_CXXFLAGS = $(AM_CXXFLAGS) \
  -pthread \
  -std=c++17 $(alsa_CFLAGS) $(tinyxml2_CFLAGS)
libexadrums_la_LDFLAGS = $(AM_LDFLAGS) \
  -pthread \
  -version-info $(exadrums_libtool_version_info)
# The -pthread compiler and linker option links with libpthread, but
# also selects various architecture-dependent settings.
libexadrums_la_LIBADD = $(alsa_LIBS) $(tinyxml2_LIBS) -lpthread -lstdc++fs -latomic
# The standard C++ library does not include libatomic on some
# architectures (armel mips mipsel). It does not hurt to always list
# it here, it will only be effective when used thanks to --as-needed.

# Distribute and embed into the library.
libexadrums_la_SOURCES = \
  Api/Config/Config_api.cpp \
  Api/Config/TriggerParameters_api.cpp \
  Api/KitCreator/KitCreator_api.cpp \
  Api/eXaDrums.cpp \
  Api/ErrorHandling.h \
  DrumKit/DrumModule/Module.cpp \
  DrumKit/DrumModule/Module.h \
  DrumKit/DrumModule/Recorder.cpp \
  DrumKit/DrumModule/Recorder.h \
  DrumKit/DrumModule/TrigSound.h \
  DrumKit/Instruments/Cymbals/TestHiHat.cpp \
  DrumKit/Instruments/Cymbals/TestHiHat.h \
  DrumKit/Instruments/Drums/TestDrum.cpp \
  DrumKit/Instruments/Drums/TestDrum.h \
  DrumKit/Instruments/Instrument.cpp \
  DrumKit/Instruments/Instrument.h \
  DrumKit/Instruments/InstrumentFactory.h \
  DrumKit/Instruments/InstrumentParameters.h \
  DrumKit/Instruments/InstrumentSoundInfo.h \
  DrumKit/Instruments/InstrumentType.h \
  DrumKit/Instruments/Pads/Pad.cpp \
  DrumKit/Instruments/Pads/Pad.h \
  DrumKit/Kits/Kit.cpp \
  DrumKit/Kits/Kit.h \
  DrumKit/Kits/KitCreator.cpp \
  DrumKit/Kits/KitManager.cpp \
  DrumKit/Triggers/Curves/Curves.h \
  DrumKit/Triggers/TriggerFactory.h \
  DrumKit/Triggers/TriggerManager.cpp \
  DrumKit/Triggers/TriggerState.h \
  DrumKit/Triggers/Triggers/ContinuousTrigger.cpp \
  DrumKit/Triggers/Triggers/ContinuousTrigger.h \
  DrumKit/Triggers/Triggers/DiscreteTrigger.cpp \
  DrumKit/Triggers/Triggers/DiscreteTrigger.h \
  DrumKit/Triggers/Triggers/Trigger.cpp \
  DrumKit/Triggers/Triggers/Trigger.h \
  IO/HddSensor.cpp \
  IO/HddSensor.h \
  IO/ISensor.h \
  IO/Serial.cpp \
  IO/Serial.h \
  IO/Spi.cpp \
  IO/Spi.h \
  IO/SpiSensor.cpp \
  IO/SpiSensor.h \
  IO/VirtualSensor.h \
  Metronome/ClickTypes.h \
  Metronome/Metronome.cpp \
  Metronome/Metronome.h \
  Metronome/MetronomeParameters.h \
  Sound/Alsa/Alsa.cpp \
  Sound/Alsa/Alsa.h \
  Sound/Alsa/AlsaParameters.cpp \
  Sound/Alsa/AlsaParameters.h \
  Sound/Mixer/Mixer.cpp \
  Sound/Mixer/Mixer.h \
  Sound/Sound.cpp \
  Sound/Sound.h \
  Sound/SoundBank/SoundBank.cpp \
  Sound/SoundBank/SoundBank.h \
  Sound/SoundProcessor/SoundProcessor.cpp \
  Sound/SoundProcessor/SoundProcessor.h \
  Sound/SoundState.h \
  Sound/Util/WavUtil.h \
  Util/Crypt.h \
  Util/Misc.h \
  Util/Parsing.h \
  Util/SimpleSafeQueue.h \
  Util/Threading.h \
  Util/Time.h

# Install into pkgincludedir, but do not distribute (it is generated
# by configure.ac).
nobase_nodist_pkginclude_HEADERS = \
  Api/eXaDrums.h

# Distribute and install into pkgincludedir.
nobase_pkginclude_HEADERS = \
  Api/Config/AlsaParams_api.h \
  Api/Config/Config_api.h \
  Api/Config/Config_api.hpp \
  Api/Config/TriggerParameters_api.h \
  Api/KitCreator/KitCreator_api.h \
  Api/KitCreator/KitCreator_api.hpp \
  Api/eXaDrums.hpp \
  Api/ErrorHandling.h \
  DrumKit/Instruments/InstrumentParameters.h \
  DrumKit/Instruments/InstrumentSoundInfo.h \
  DrumKit/Instruments/InstrumentType.h \
  DrumKit/Kits/KitCreator.h \
  DrumKit/Kits/KitManager.h \
  DrumKit/Kits/KitParameters.h \
  DrumKit/Triggers/Curves/CurveType.h \
  DrumKit/Triggers/TriggerLocation.h \
  DrumKit/Triggers/TriggerManager.h \
  DrumKit/Triggers/TriggerParameters.h \
  DrumKit/Triggers/TriggerType.h \
  IO/SensorType.h \
  IO/SensorsConfig.h \
  Sound/Alsa/AlsaParams.h \
  Sound/InstrumentSoundType.h \
  Util/Enums.h \
  Util/Xml.h
