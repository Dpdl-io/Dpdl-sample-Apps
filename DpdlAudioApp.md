# DpdlSoundAudioApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io

    
##  DpdlSoundAudioApp - A simple Dpdl application to emit sound waves via various audio backends available

**Dpdl source code**:
[app/dpdlsoundaudioapp/](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdlsoundaudioapp)

### Description

The Dpdl app '**DpdlSoundAudioApp**' is a simple audio application that emits sound waves via various audio backends available on the platform.

The sound capability is implemented with embedded C code wihin Dpdl that makes use of the cross-platform 'libsoundio' C library to handle audio input and output.
The library provides an abstraction layer for accessing audio input/output capabilities via variouns configurable backends.
**'libsoundio':** https://github.com/andrewrk/libsoundio

### Suported Audio backends:

- JACK
- PulseAudio
- ALSA
- CoreAudio
- WASAPI

### Supported OS:

Windows 7+
MacOS 10.10+
Linux 3.7+




