# libeXaDrums
A shared library for <a href="https://github.com/SpintroniK/eXaDrums">eXaDrums</a>.

> eXaDrums is a drum module that is compatible with most Linux distributions. 
It was originally created for the Raspberry Pi 2B and its official 7" touchscreen. 
Please check out my other <a href="https://github.com/SpintroniK/eXaDrums">repository</a> for more details about eXaDrums.

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
sudo apt-get install libasound2-dev libtinyxml2-dev build-essential 
```
Note that you also need build-essential to build the project.

You may also want to install git, so that you can clone this repository and install from it: 
```
sudo apt-get install git
git clone https://github.com/SpintroniK/libeXaDrums.git 
```

### Installation

Now that you have all dependencies, you can compile libeXaDrums.
Go to the `Release` directory and type `make all` in you terminal: 
```
cd libeXaDrums/Release
make all 
```

If you have multiple cores/threads, you can specify it by appending the option -jn, where n is the number of threads that you want to use for the compilation. 

Example, for four threads type: <code>make -j4 all</code>.

### Configuration

## Usage

## License

## Links
