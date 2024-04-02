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
        format.nSamplesPerSec = 1000; // Adjust if necessary
        format.wBitsPerSample = 8;
        format.nBlockAlign = (format.nChannels * format.wBitsPerSample / 8); // Quadruple the buffer size
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

        const double amplitude = 1300000.0;
        const double decayFactor = 0.98; // Decay factor to simulate the "bing" sound fading out

        for (int i = 0; i < numSamples; ++i)
        {
            double t = static_cast<double>(i) / format.nSamplesPerSec;
            double waveValue = amplitude * std::sin(3.1415926 * frequency * t);
            waveValue *= std::pow(decayFactor, i); // Apply exponential decay
            samples[i] = static_cast<short>(waveValue);
        }

        ZeroMemory(&header, sizeof(header));
        header.lpData = reinterpret_cast<LPSTR>(&samples[0]);
        header.dwBufferLength = sizeof(samples[0]) * samples.size();

        MMRESULT result = waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
        result = waveOutWrite(hWaveOut, &header, sizeof(header));

        while (waveOutWrite(hWaveOut, &header, sizeof(header)) == WAVERR_STILLPLAYING) {
            // Additional audio playback if necessary
        }

        waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
    }
};

#endif
