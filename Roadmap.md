# LibeXaDrums Roadmap

This document outlines the development plan from a high level and will be updated as progress is made.

## Legend of annotations

| Mark               | Description                     |
| ----------         | ------------------------------- |
| :construction:     | work not started - scheduled    |
| :heavy_check_mark: | work completed                  |
| :pencil:           | on-going work                   |

## Current version

### 0.8.0

- :heavy_check_mark: C++23.
- :pencil: USB MIDI input.

## Future versions

### 0.9.0

- :construction: Instrument module system.
- :construction: More trigger & instrument types.

### 1.0.0

## Documentation

- :construction: Doxygen: document code.
- :construction: API documentation.

## Past versions

### 0.7.0

- :heavy_check_mark: Improve recorder stuff (auto gain, etc.).
- :heavy_check_mark: More generic SPI sensor reading (multiple devices, etc.).
- :heavy_check_mark: Improve factories
- :heavy_check_mark: Serial MIDI input support.
- :heavy_check_mark: Use C++20

### 0.6.0

- :heavy_check_mark: Recorder export to PCM (wav).
- :heavy_check_mark: Simple calibration stuff.

### 0.5.0

- :heavy_check_mark: Add export configuration feature.
- :heavy_check_mark: Add import configuration feature.
- :heavy_check_mark: Add GetVersion() to API.
- :heavy_check_mark: Document API.
- :heavy_check_mark: Bug fix: check if instrument's triggers exist.
- :heavy_check_mark: Add trigger sensitivity (gain).
- :heavy_check_mark: Fix trig on start bug (to be improved).
- :heavy_check_mark: Add rhythm coach score (done in eXaDrums directly).
- :heavy_check_mark: Create instrument only if enough triggers are available.
- :heavy_check_mark: Fix metronome volume bug.

### 0.4.2

- :heavy_check_mark: Build successfully with clang++-7.
- :heavy_check_mark: Version.h.in instead of eXaDrums.h.in.
- :heavy_check_mark: Fix Readme (installation procedure -- checkout debian branch first).
