# libeXaDrums

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6fd320220fc24258a77b70ac716e4ee1)](https://app.codacy.com/app/SpintroniK/libeXaDrums?utm_source=github.com&utm_medium=referral&utm_content=SpintroniK/libeXaDrums&utm_campaign=Badge_Grade_Dashboard)

 ExaDrums is a software drum module that allows drummers play with
 custom-made drum kits.
 This C++ library provides the most common features of a drum module.
 Its associated graphical user interface can be found in a separate
 repository: <https://github.com/SpintroniK/eXaDrums.>

 Each drum kit is made of instruments that can be individually
 controlled.

 A built-in metronome can be combined with a rhythm coach to make
 practice sessions easier and efficient.

 The drum triggers can be adjusted so that their response feels as
 natural as possible, and different sensor interfaces include
 external sensors.

 Although eXaDrums is usable as a drum module, it is still a
 young project. As such, some features are not yet implemented
 or are still experimental.

## Table of content

- [Installation and configuration](#installation-and-configuration)
  - [Dependencies](#dependencies)
  - [Building libeXaDrums](#building-libexadrums)
  - [Installation](#installation)
  - [Configuration](#configuration)
- [Usage](#usage)

## Installation and configuration

Libexadrums is available from the Debian unstable and testing distributions, as well as Ubuntu >=19.10.
If you wish to install the latest version of the library, you can build the packages from the Github repositorie.

### Dependencies

libeXaDrums depends on Alsa, TinyXml2 and minizip. You can install those two libraries using this command line:

```shell
sudo apt install libasound2-dev libtinyxml2-dev libminizip-dev
```

LibeXaDrums also depends on build-essential, autotools and pkg-config in order to build and install the binaries:

```shell
sudo apt install autoconf automake libtool build-essential pkg-config
```

If you wish to build the Debian packages (which is the recommended way to install
the library), you will need to install debhelper:

```shell
sudo apt install debhelper
```

You will also need to install git, so that you can clone this repository:

```shell
sudo apt install git
git clone https://github.com/SpintroniK/libeXaDrums.git
```

### Building libeXaDrums

Now that you have all dependencies, you can build the Debian packages.
Make sure you have dehelper installed, and then checkout the debian branch
from your cloned repository:

```shell
cd libeXaDrums
git checkout debian
```

Then you can build the package:

```shell
dpkg-buildpackage -b -uc -us
```

If you have multiple cores/threads, you can speed up the build process by appending the option -jn to dpkg-buildpackage, where n is the number of threads that you want to use for the compilation.
Example, for four threads type: `dpkg-buildpackage -b -uc -us -j4`.

### Installation

The Debian packages are built in the parent directory, so you should be able to install them by using dpkg (don't forget to install them as root):

```shell
cd ..
sudo apt install ./libexadrums0_[...].deb
sudo apt install ./libexadrums-dev[...].deb
```

### Configuration

## Usage

The library is self documented.
