# libeXaDrums
A shared library for [eXaDrums](https://github.com/SpintroniK/eXaDrums).

> eXaDrums is a drum module that is compatible with most Linux distributions. 
It was originally created for the Raspberry Pi 2B and its official 7" touchscreen. 
Please check out my other [repository](https://github.com/SpintroniK/eXaDrums) for more details about eXaDrums.

## Table of content

- [Installation and Configuration](#installation)
    - [Dependencies](#dependencies)
    - [Installation](#installation)
    - [Configuration](#configuration)
- [Usage](#usage)
- [License](#license)
- [Links](#links)

## Installation

### Dependencies

libeXaDrums depends on Alsa and TinyXml2. You can install those two libraries using this command line: <br />
```
sudo apt install libasound2-dev libtinyxml2-dev
```
LibeXaDrums also depends on build-essential and autotools in order to build and install the binaries: 
```
sudo apt install autoconf automake libtool build-essential 
```
If you wish to build the Debian packages, you will need to install debhelper and pkg-config: 
```
sudo apt install debhelper pkg-config
```
You may also want to install git, so that you can clone this repository and install from it: 
```
sudo apt install git
git clone https://github.com/SpintroniK/libeXaDrums.git 
```

### Building libeXaDrums

Now that you have all dependencies, you can build libeXaDrums: 
```
cd libeXaDrums
autoreconf -fi
./configre
make
```
or you can build the Debian packages: 
```
cd libeXaDrums
dpkg-buildpackage -b -uc
sudo dpkg -i libexadrums0_[...].deb
sudo dpkg -i libexadrums-dev[...].deb
```
If you have multiple cores/threads, you can specify it by appending the option -jn to dpkg-buildpackage, where n is the number of threads that you want to use for the compilation. 
Example, for four threads type: `dpkg-buildpackage -b -uc -j4`.

### Installing libeXaDrums

If you have built libeXaDrums using make, use:

```sudo make install```

otherwise, if you built the Debian packages, install them normally: 

```
sudo dpkg -i libexadrums0_[...].deb
sudo dpkg -i libexadrums-dev[...].deb
```

## Usage

## License

## Links
