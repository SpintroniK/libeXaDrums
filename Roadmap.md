# LibeXaDrums roadmap

This document outlines the development plan from a high level and will be updated as progress is made.

## Legend of annotations

| Mark       | Description                     |
| ---------- | ------------------------------- |
| open box   | work not started - scheduled    |
| check mark | work completed                  |
| &#9997;    | on-going work                   |

## Current version

### 0.7.0

- [X] Improve recorder stuff (auto gain, etc.).
- &#9997; More generic SPI sensor reading (multiple devices, etc.).
- &#9997; Improve factories
- &#9997; Use C++20

## Future versions

### 0.8.0

- [ ] More trigger types.

### 0.9.0

- [ ] Instrument builder.

### 1.0.0

## Documentation

- [ ] Doxygen: document code.
- [ ] API documentation.

## Past versions

### 0.6.0

- [X] Recorder export to PCM (wav).
- [X] Simple calibration stuff.

### 0.5.0

- [X] Add export configuration feature.
- [X] Add import configuration feature.
- [X] Add GetVersion() to API.
- [X] Document API.
- [X] Bug fix: check if instrument's triggers exist.
- [X] Add trigger sensitivity (gain).
- [X] Fix trig on start bug (to be improved).
- [X] Add rhythm coach score (done in eXaDrums directly).
- [X] Create instrument only if enough triggers are available.
- [X] Fix metronome volume bug.

### 0.4.2

- [X] Build successfully with clang++-7.
- [X] Version.h.in instead of eXaDrums.h.in.
- [X] Fix Readme (installation procedure -- checkout debian branch first).
