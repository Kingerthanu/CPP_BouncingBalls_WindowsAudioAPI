#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

#include <Windows.h>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <iostream>

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
        format.nSamplesPerSec = 44100; // Adjusted to standard audio sample rate
        format.wBitsPerSample = 16; // Increased for better audio quality
        format.nBlockAlign = (format.nChannels * format.wBitsPerSample / 8);
        format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
        format.cbSize = 0;

        ZeroMemory(&header, sizeof(header));
        MMRESULT result = waveOutOpen(&hWaveOut, WAVE_MAPPER, &format, 0, 0, WAVE_FORMAT_DIRECT);
    }

    ~Audio_Driver()
    {
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
        waveOutReset(hWaveOut); // Reset the audio device to stop any ongoing playback
        waveOutClose(hWaveOut); // Close the audio device
    }

    void Write_Sound_Thread(const double& velocityX, const double& velocityY)
    {
        std::thread soundThread(&Audio_Driver::Write_Sound, this, velocityX, velocityY);
        soundThread.detach(); // Detach the thread after sound playback
    }

    void Write_Sound(const double& velocityX, const double& velocityY)
    {
    
        //std::cout << "Sounding...\n";

        // Define frequency and duration for the ding sound
        const double dingFrequency =  335.134 + (velocityX * 5000.0) + (velocityY * 5000.0); // High-pitch frequency
        const double dingDuration = 0.01; // Duration of the ding sound in seconds

        // Calculate the number of samples for the ding sound
        const int dingNumSamples = static_cast<int>(format.nSamplesPerSec * dingDuration);

        // Amplitude and decay factor for the ding sound
        const double dingAmplitude = 0.5 * 32767.0; // Half of the maximum amplitude to prevent clipping
        const double dingDecayFactor = 0.995; // Adjusted for a smoother decay

        // Vector to hold the ding sound wave samples
        std::vector<short> dingSamples(dingNumSamples);

        // Generate the ding sound wave samples
        for (unsigned int i = 0; i < dingNumSamples; ++i)
        {
            double t = (double)(i) / format.nSamplesPerSec;
            double waveValue = dingAmplitude * std::sin(2 * 3.1415926 * dingFrequency * t);
            waveValue *= std::pow(dingDecayFactor, i);
            dingSamples[i] = (short)(waveValue);
        }

        // Prepare the header for playback of the ding sound
        ZeroMemory(&header, sizeof(header));
        header.lpData = reinterpret_cast<LPSTR>(&dingSamples[0]);
        header.dwBufferLength = sizeof(dingSamples[0]) * dingSamples.size();

        // Prepare the ding sound buffer
        waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
        waveOutWrite(hWaveOut, &header, sizeof(header));

        

        // Wait for ding sound playback to finish
        waveOutWrite(hWaveOut, &header, sizeof(header));
        Sleep(500);

        // Unprepare the ding sound buffer
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
    }

};

#endif
