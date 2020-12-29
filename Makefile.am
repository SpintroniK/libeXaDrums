## Process this file with automake to produce Makefile.in

# Copyright (C) 2018-2021 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2021 Nicolas Boulenguez <nicolas@debian.org>

# Unless otherwise specified, the numbers refer to
# https://www.gnu.org/software/automake/manual/automake.html

######################################################################
# https://www.gnu.org/software/gettext/manual/gettext.html
# 13.4.8 aclocal.m4 at top level

# Cache shared with autoconf.
ACLOCAL_AMFLAGS = -I m4

######################################################################
# 8 building programs and libraries

# Delegate library handling to libtool.
lib_LTLIBRARIES = libexadrums.la

# libtool 7.3 updating library version information
# Downstream packagers may have to override the SO version.
exadrums_libtool_version_info = 1:0:0

libexadrums_la_CXXFLAGS = \
  -Wall \
  -pthread \
  -std=c++17 $(alsa_CFLAGS) $(tinyxml2_CFLAGS) $(minizip_CFLAGS)
libexadrums_la_LDFLAGS = \
  -Wl,--as-needed \
  -Wl,--no-allow-shlib-undefined \
  -Wl,--no-copy-dt-needed-entries \
  -Wl,--no-undefined \
  -pthread \
  -version-info $(exadrums_libtool_version_info)
# The -pthread compiler and linker option links with libpthread, but
# also selects various architecture-dependent settings.
libexadrums_la_LIBADD = $(alsa_LIBS) $(tinyxml2_LIBS) $(minizip_LIBS) -lpthread -lstdc++fs -latomic
# The standard C++ library does not include libatomic on some
# architectures (armel mips mipsel). It does not hurt to always list
# it here, it will only be effective when used thanks to --as-needed.

# Distribute and embed into the library.
libexadrums_la_SOURCES = \
  Api/Config/Config_api.cpp \
  Api/Config/TriggerParameters_api.cpp \
  Api/KitCreator/KitCreator_api.cpp \
  Api/eXaDrums.cpp \
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
  Util/ErrorHandling.h \
  Util/Misc.h \
  Util/Parsing.h \
  Util/SimpleSafeQueue.h \
  Util/Threading.h \
  Util/Time.h \
  Util/Zip.h

# Install into pkgincludedir, but do not distribute (it is generated
# by configure.ac).
nobase_nodist_pkginclude_HEADERS = \
  Api/Version.h

# Distribute and install into pkgincludedir.
nobase_pkginclude_HEADERS = \
  Api/Config/AlsaParams_api.h \
  Api/Config/Config_api.h \
  Api/Config/Config_api.hpp \
  Api/Config/TriggerParameters_api.h \
  Api/KitCreator/KitCreator_api.h \
  Api/KitCreator/KitCreator_api.hpp \
  Api/eXaDrums.h \
  Api/eXaDrums.hpp \
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
  Util/ErrorHandling.h \
  Util/Xml.h \
  Util/Zip.h

######################################################################
# 12 what gets installed

# Distribute and install into docdir.
dist_doc_DATA = README.md

# Install in an architecture-dependent directory, do not distribute.
pkgexecconfigdir = $(libdir)/pkgconfig
pkgexecconfig_DATA = exadrums.pc

# autoconf 4.8.2 Installation Directory Variables
# Substituting from here instead of from configure.ac ensures that the
# user can override prefix on the Make command line.
edit = sed \
  -e 's|@PACKAGE_NAME[@]|$(PACKAGE_NAME)|g' \
  -e 's|@PACKAGE_URL[@]|$(PACKAGE_URL)|g' \
  -e 's|@PACKAGE_VERSION[@]|$(PACKAGE_VERSION)|g' \
  -e 's|@includedir[@]|$(includedir)|g' \
  -e 's|@libdir[@]|$(libdir)|g'
exadrums.pc: Makefile
	rm -f $@ $@.tmp
	srcdir=''; \
	  test -f ./$@.in || srcdir=$(srcdir)/; \
	  $(edit) $${srcdir}$@.in >$@.tmp
	mv $@.tmp $@
exadrums.pc: $(srcdir)/exadrums.pc.in

######################################################################
# 13 what gets cleaned

# Remove files created by Makefile.
CLEANFILES = \
  exadrums.pc

# Should silent `rm .gitignore && git status`.
MAINTAINERCLEANFILES = \
  Makefile.in \
  aclocal.m4 \
  ar-lib \
  compile \
  config.guess \
  config.h.in \
  config.sub \
  configure \
  depcomp \
  install-sh \
  ltmain.sh \
  m4/* \
  missing

######################################################################
# 14 what goes in a distribution

# Distribute (in the tarball created by 'make dist-gzip').
EXTRA_DIST = \
  LICENSE \
  Roadmap.md \
  bootstrap \
  exadrums.pc.in
