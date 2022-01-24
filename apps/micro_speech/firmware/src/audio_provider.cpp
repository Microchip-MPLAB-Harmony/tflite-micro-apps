/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "audio_provider.h"
#include "micro_model_settings.h"
#include "app_audio.h"
#include "user.h"

// Feed microphone samples
#if 1
extern AUDIO_DATA_TYPE micCaptureBuffer[];

namespace {
int16_t g_audio_data[kMaxAudioSampleSize];
}  // namespace

TfLiteStatus GetAudioSamples(tflite::ErrorReporter* error_reporter,
                             int start_ms, int duration_ms,
                             int* audio_samples_size, int16_t** audio_samples) {
  
  // This should only be called when the main thread notices that the latest
  // audio sample data timestamp has changed, so that there's new data in the
  // capture ring buffer. The ring buffer will eventually wrap around and
  // overwrite the data, but the assumption is that the main thread is checking
  // often enough and the buffer is large enough that this call will be made
  // before that happens.
  const int start_offset = start_ms * (kAudioSampleFrequency / 1000);
  const int duration_sample_count =
      duration_ms * (kAudioSampleFrequency / 1000);
  for (int i = 0; i < duration_sample_count; ++i) {
    const int capture_index = (start_offset + i) % kMicCaptureBufferSize;
#if AUDIO_DATA_WIDTH == 32
    g_audio_data[i] = micCaptureBuffer[capture_index]>>16;
#elif AUDIO_DATA_WIDTH == 16
    g_audio_data[i] = micCaptureBuffer[capture_index];
#endif
  }
  
  *audio_samples_size = kMaxAudioSampleSize;
  *audio_samples = g_audio_data;
  return kTfLiteOk;
}

int32_t LatestAudioTimestamp() {
  return app_audioData.audio_timestamp;

}

// Feed test samples
#else

#include "no_1000ms_sample_data.h"
#include "yes_1000ms_sample_data.h"

namespace {
int16_t g_dummy_audio_data[kMaxAudioSampleSize];
int32_t g_latest_audio_timestamp = 0;
}  // namespace

TfLiteStatus GetAudioSamples(tflite::ErrorReporter* error_reporter,
                             int start_ms, int duration_ms,
                             int* audio_samples_size, int16_t** audio_samples) {
  const int yes_start = (0 * kAudioSampleFrequency) / 1000;
  const int yes_end = (1000 * kAudioSampleFrequency) / 1000;
  const int no_start = (8000 * kAudioSampleFrequency) / 1000;
  const int no_end = (9000 * kAudioSampleFrequency) / 1000;
  const int wraparound = (16000 * kAudioSampleFrequency) / 1000;
  const int start_sample = (start_ms * kAudioSampleFrequency) / 1000;
  
    const int duration_sample_count =
      duration_ms * (kAudioSampleFrequency / 1000);
    
  for (int i = 0; i < kMaxAudioSampleSize; ++i) {
    const int sample_index = (start_sample + i) % wraparound;
    int16_t sample;
    if ((sample_index >= yes_start) && (sample_index < yes_end)) {
      sample = g_yes_1000ms_sample_data[sample_index - yes_start];
    } else if ((sample_index >= no_start) && (sample_index < no_end)) {
      sample = g_no_1000ms_sample_data[sample_index - no_start];
    } else {
      sample = 0;
    }
    g_dummy_audio_data[i] = sample;
  }
  *audio_samples_size = kMaxAudioSampleSize;
  *audio_samples = g_dummy_audio_data;
  
  return kTfLiteOk;
}

int32_t LatestAudioTimestamp() {
  return g_latest_audio_timestamp = g_latest_audio_timestamp+100;
}
#endif
