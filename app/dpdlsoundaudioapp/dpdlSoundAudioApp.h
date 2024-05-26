# DpdlSoundAudioApp - a sample Sound/Audio application written with Dpdl with embedded C code
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/dpdlsoundaudioapp/dpdlSoundAudioApp.h
#
# Example: Sample Dpdl code 'DpdlSoundAudioApp' that emits a sine wave audio sound using the 'libsoundio' C library
#			Commands:
#						'p' -> pause
#						'u' -> unpause
#						'P' -> pause from callback
#						'c' -> clear buffer
#						'q' -> terminate
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#


# main
println("init dpdlSoundAudioApp()")
println("")

println("start emitting sine audio wave...")

dpdl_stack_push("dpdlstack:myaudio", "dpdlbuf_myresult", "dpdl:compile", "dpdl:-I./DpdlLibs/app/dpdlsoundaudioapp/include", "dpdl:-L./DpdlLibs/app/dpdlsoundaudioapp/lib", "dpdl:-lsoundio")

>>c
#include "soundio/soundio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern void dpdl_stack_buf_put(char *buf);

static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;
static volatile bool want_pause = false;

static void write_sample_s16ne(char *ptr, double sample) {
    int16_t *buf = (int16_t *)ptr;
    double range = (double)INT16_MAX - (double)INT16_MIN;
    double val = sample * range / 2.0;
    *buf = val;
}
static void write_sample_s32ne(char *ptr, double sample) {
    int32_t *buf = (int32_t *)ptr;
    double range = (double)INT32_MAX - (double)INT32_MIN;
    double val = sample * range / 2.0;
    *buf = val;
}
static void write_sample_float32ne(char *ptr, double sample) {
    float *buf = (float *)ptr;
    *buf = sample;
}
static void write_sample_float64ne(char *ptr, double sample) {
    double *buf = (double *)ptr;
    *buf = sample;
}
static void (*write_sample)(char *ptr, double sample);

static void write_callback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max) {
    double float_sample_rate = outstream->sample_rate;
    double seconds_per_frame = 1.0 / float_sample_rate;
    struct SoundIoChannelArea *areas;
    int err;
    int frames_left = frame_count_max;
    for (;;) {
        int frame_count = frames_left;
        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "unrecoverable stream error: %s\n", soundio_strerror(err));
            exit(1);
        }
        if (!frame_count)
            break;
        const struct SoundIoChannelLayout *layout = &outstream->layout;
        double pitch = 440.0;
        double radians_per_second = pitch * 2.0 * PI;
        for (int frame = 0; frame < frame_count; frame += 1) {
            double sample = sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
            for (int channel = 0; channel < layout->channel_count; channel += 1) {
                write_sample(areas[channel].ptr, sample);
                areas[channel].ptr += areas[channel].step;
            }
        }
        seconds_offset += seconds_per_frame * frame_count;
        if ((err = soundio_outstream_end_write(outstream))) {
            if (err == SoundIoErrorUnderflow)
                return;
            fprintf(stderr, "unrecoverable stream error: %s\n", soundio_strerror(err));
            exit(1);
        }
        frames_left -= frame_count;
        if (frames_left <= 0)
            break;
    }
    soundio_outstream_pause(outstream, want_pause);
}

static void underflow_callback(struct SoundIoOutStream *outstream) {
    static int count = 0;
    fprintf(stderr, "underflow %d\n", count++);
}

int main(int argc, char **argv) {
    char *exe = argv[0];
    enum SoundIoBackend backend = SoundIoBackendNone;
    char *device_id = NULL;
    bool raw = false;
    char *stream_name = NULL;
    double latency = 0.0;
    int sample_rate = 0;

    struct SoundIo *soundio = soundio_create();
    if (!soundio) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    int err = (backend == SoundIoBackendNone) ?
        soundio_connect(soundio) : soundio_connect_backend(soundio, backend);
    if (err) {
        fprintf(stderr, "Unable to connect to backend: %s\n", soundio_strerror(err));
        return 1;
    }
    fprintf(stderr, "Backend: %s\n", soundio_backend_name(soundio->current_backend));
    soundio_flush_events(soundio);
    int selected_device_index = -1;
    if (device_id) {
        int device_count = soundio_output_device_count(soundio);
        for (int i = 0; i < device_count; i += 1) {
            struct SoundIoDevice *device = soundio_get_output_device(soundio, i);
            if (strcmp(device->id, device_id) == 0 && device->is_raw == raw) {
                selected_device_index = i;
                break;
            }
        }
    } else {
        selected_device_index = soundio_default_output_device_index(soundio);
    }
    if (selected_device_index < 0) {
        fprintf(stderr, "Output device not found\n");
        return 1;
    }
    struct SoundIoDevice *device = soundio_get_output_device(soundio, selected_device_index);
    if (!device) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }
    fprintf(stderr, "Output device: %s\n", device->name);
    if (device->probe_error) {
        fprintf(stderr, "Cannot probe device: %s\n", soundio_strerror(device->probe_error));
        return 1;
    }
    struct SoundIoOutStream *outstream = soundio_outstream_create(device);
    outstream->write_callback = write_callback;
    outstream->underflow_callback = underflow_callback;
    outstream->name = stream_name;
    outstream->software_latency = latency;
    outstream->sample_rate = sample_rate;
    if (soundio_device_supports_format(device, SoundIoFormatFloat32NE)) {
        outstream->format = SoundIoFormatFloat32NE;
        write_sample = write_sample_float32ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatFloat64NE)) {
        outstream->format = SoundIoFormatFloat64NE;
        write_sample = write_sample_float64ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatS32NE)) {
        outstream->format = SoundIoFormatS32NE;
        write_sample = write_sample_s32ne;
    } else if (soundio_device_supports_format(device, SoundIoFormatS16NE)) {
        outstream->format = SoundIoFormatS16NE;
        write_sample = write_sample_s16ne;
    } else {
        fprintf(stderr, "No suitable device format available.\n");
        return 1;
    }
    if ((err = soundio_outstream_open(outstream))) {
        fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
        return 1;
    }
    fprintf(stderr, "Software latency: %f\n", outstream->software_latency);
    printf("Enter one of the commands below and press ENTER\n");
    fprintf(stderr,
            "'p' - pause\n"
            "'u' - unpause\n"
            "'P' - pause from within callback\n"
            "'c' - clear buffer\n"
            "'q' - quit\n");
    if (outstream->layout_error)
        fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));
    if ((err = soundio_outstream_start(outstream))) {
        fprintf(stderr, "unable to start device: %s\n", soundio_strerror(err));
        return 1;
    }
    for (;;) {
        soundio_flush_events(soundio);
        int c = getc(stdin);
        if (c == 'p') {
            fprintf(stderr, "pausing result: %s\n",
                    soundio_strerror(soundio_outstream_pause(outstream, true)));
        } else if (c == 'P') {
            want_pause = true;
        } else if (c == 'u') {
            want_pause = false;
            fprintf(stderr, "unpausing result: %s\n",
                    soundio_strerror(soundio_outstream_pause(outstream, false)));
        } else if (c == 'c') {
            fprintf(stderr, "clear buffer result: %s\n",
                    soundio_strerror(soundio_outstream_clear_buffer(outstream)));
        } else if (c == 'q') {
            break;
        } else if (c == '\r' || c == '\n') {
            // ignore
        } else {
            fprintf(stderr, "Unrecognized command: %c\n", c);
        }
    }

    // store the audio backend name on the dpdl stack
    char *audio_backend_name = soundio_backend_name(soundio->current_backend);
    dpdl_stack_buf_put(audio_backend_name);


    soundio_outstream_destroy(outstream);
    soundio_device_unref(device);
    soundio_destroy(soundio);

    return 0;
}
<<
int exit_code = dpdl_exit_code()
println("embedded C exit code: " + exit_code);

string buf = dpdl_stack_buf_get("dpdlbuf_myresult")

println("Audio Backend used: " + buf)

println("")


