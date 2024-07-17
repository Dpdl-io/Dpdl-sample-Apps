# DpdlSoundAudioApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io

    
##  DpdlSoundAudioApp - A sample Dpdl application to emit audio sound waves via various audio backends available

**Dpdl source code**:
[app/dpdlsoundaudioapp/](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdlsoundaudioapp)

Main source file:
[dpdlSoundAudioApp.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlsoundaudioapp/dpdlSoundAudioApp.h)

### Description

The Dpdl app '**DpdlSoundAudioApp**' is a sample audio application that emits sound waves via various audio backends available on the platform.

The sound capability is implemented with <ins>embedded C code wihin Dpdl</ins> (compiled at rutime) that makes use of the cross-platform 'libsoundio' C library to handle audio input and output.
The library provides an abstraction layer for accessing audio input/output capabilities via variouns configurable backends.
**'libsoundio':** https://github.com/andrewrk/libsoundio

### Suported Audio backends:

- JACK
- PulseAudio
- ALSA
- CoreAudio
- WASAPI

### Supported OS:

- Windows 7+
- MacOS 10.10+
- Linux 3.7+

### Command actions avalable

The following keyboard commands are available once the app is running and emitting sound:

```
'p' -> pause
'u' -> unpause
'P' -> pause from callback
'c' -> clear buffer
'q' -> terminate
```

