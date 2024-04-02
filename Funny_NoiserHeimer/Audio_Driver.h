#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

#include <Windows.h>
#include <vector>
#include <random>
#include <thread>


class Audio_Driver
{
private:
    WAVEFORMATEX format;
    HWAVEOUT hWaveOut;
    WAVEHDR header;

public:
    Audio_Driver()
    {
        format.wFormatTag = WAVE_FORMAT_PCM;
        format.nChannels = 1;
        format.nSamplesPerSec = 44100; // Adjust if necessary
        format.wBitsPerSample = 16;
        format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
        format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
        format.cbSize = 0;
        MMRESULT result = waveOutOpen(&hWaveOut, WAVE_MAPPER, &format, 0, 0, WAVE_FORMAT_DIRECT);
  
    }

    void Write_Sound_Thread(const double& frequency, const double& duration)
    {
        std::thread soundThread(&Audio_Driver::Write_Sound, this, frequency, duration);
        soundThread.detach(); // Join the thread after sound playback
    }

    void Write_Sound(const double& frequency, const double& duration)
    {
        const int numSamples = static_cast<int>(format.nSamplesPerSec * duration);
        std::vector<short> samples(numSamples);

        const double amplitude = 10000.0;
        const double decayFactor = 0.98; // Decay factor to simulate the sound fading out

        for (int i = 0; i < numSamples; ++i)
        {
            double t = static_cast<double>(i) / format.nSamplesPerSec;

            // Generate a mixture of harmonics using sine waves
            double waveValue = amplitude * (
                std::sin(2 * 3.1415926 * frequency * t) +
                0.5 * std::sin(2 * 3.1415926 * 2 * frequency * t) +
                0.25 * std::sin(2 * 3.1415926 * 3 * frequency * t)
                );

            // Apply exponential decay to simulate fading out
            waveValue *= std::pow(decayFactor, i);

            samples[i] = static_cast<short>(waveValue);
        }

        // Prepare audio header and write sound
        ZeroMemory(&header, sizeof(header));
        header.lpData = reinterpret_cast<LPSTR>(&samples[0]);
        header.dwBufferLength = sizeof(samples[0]) * samples.size();

        MMRESULT result = waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
        result = waveOutWrite(hWaveOut, &header, sizeof(header));

        while (waveOutWrite(hWaveOut, &header, sizeof(header)) == WAVERR_STILLPLAYING) {
            // Waiting for playback to finish
        }

        waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
    }


};
#endif