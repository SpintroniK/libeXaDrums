# LibeXaDrums Roadmap

This document outlines the development plan from a high level and will be updated as progress is made.

## Legend of annotations

| Mark | Description                  |
| ---- | ---------------------------- |
| 🚧   | work not started - scheduled |
| ✔️ | work completed               |
| 📝   | on-going work                |

## Current version

### 0.8.0

- ✔️ C++23.
- 📝 USB MIDI input.

## Future versions

### 0.9.0

- 🚧 Multi-layer sounds
- 🚧 Round-robin
- 🚧 More trigger & instrument types.

### 1.0.0

## Documentation

- 🚧 Doxygen: document code.
- 🚧 API documentation.

## Past versions

### 0.7.0

- ✔️ Improve recorder stuff (auto gain, etc.).
- ✔️ More generic SPI sensor reading (multiple devices, etc.).
- ✔️ Improve factories
- ✔️ Serial MIDI input support.
- ✔️ Use C++20

### 0.6.0

- ✔️ Recorder export to PCM (wav).
- ✔️ Simple calibration stuff.

### 0.5.0

- ✔️ Add export configuration feature.
- ✔️ Add import configuration feature.
- ✔️ Add GetVersion() to API.
- ✔️ Document API.
- ✔️ Bug fix: check if instrument's triggers exist.
- ✔️ Add trigger sensitivity (gain).
- ✔️ Fix trig on start bug (to be improved).
- ✔️ Add rhythm coach score (done in eXaDrums directly).
- ✔️ Create instrument only if enough triggers are available.
- ✔️ Fix metronome volume bug.

### 0.4.2

- ✔️ Build successfully with clang++-7.
- ✔️ Version.h.in instead of eXaDrums.h.in.
- ✔️ Fix Readme (installation procedure -- checkout debian branch first).
