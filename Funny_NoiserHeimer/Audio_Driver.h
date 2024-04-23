#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

#include <Windows.h>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <iostream>
#include "SpectrogramWindow.h"

class Audio_Driver
{
        private:
            WAVEFORMATEX format;
            HWAVEOUT hWaveOut;
            WAVEHDR header;
            Spectrogram_Window& analogCallback;
            


        // ~~~~~~~~Constants of Feedback~~~~~~~~~~~~

            const double dingDuration = 0.01; // Duration of the ding sound in seconds

            // Calculate the number of samples for the ding sound     (44100 is hard-baked as we predeterminately know our nSamplesPerSec).
            const int dingNumSamples = (int)(22050 * dingDuration);

            // Amplitude and decay factor for the ding sound
            const double dingAmplitude = 0.5 * 32767.0; // Half of the maximum amplitude to prevent clipping

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        public:
            Audio_Driver(Spectrogram_Window& callbackee) : analogCallback(callbackee)
            {

                format.wFormatTag = WAVE_FORMAT_PCM;
                format.nChannels = 1;
                format.nSamplesPerSec = 22050; // Adjusted to standard audio sample rate
                format.wBitsPerSample = 16; // Increased for better audio quality
                format.nBlockAlign = (format.nChannels * format.wBitsPerSample / 8);  // Tell Ourselves How To Chunk Out Our Bits With The Given Parts We Have  (I.E. Halving Block Alignment To Fit 2-Channels In One Check, Etc.)
                format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;  // We Have This Many Samples To Do, And This Many Blocks To Do It For
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
                const double dingFrequency =  (15.134) + (velocityX * 10000.0) + (velocityY * 10000.0); // High-pitch frequency

                // Vector to hold the ding sound wave samples
                std::vector<short> dingSamples(dingNumSamples);

                // Generate the ding sound wave samples with fade-in and fade-out
                for (unsigned int i = 0; i < dingNumSamples; ++i)
                {
                    double t = (double)(i) / format.nSamplesPerSec;
                    double fadeFactor = 1.0;  // Magnitude Of Our Ding's Frequency We Will Represent In Our Fading

                    // Apply Fade-In Effect
                    if (i < dingNumSamples * 0.5) { // Adjust Fade-In Duration As Needed

                        fadeFactor = (double)(i) / (dingNumSamples * 0.5); // Linear fade-in

                    }

                    // Apply Fade-Out Effect
                    else if (i > dingNumSamples * 0.5) { // Adjust fade-out duration as needed

                        fadeFactor = 1.0 - (double)(i - dingNumSamples * 0.5) / (dingNumSamples * 0.5); // Linear fade-out

                    }

                    double waveValue = dingAmplitude * fadeFactor * std::sin(2 * 3.1415926 * dingFrequency * t);
                    dingSamples[i] = static_cast<short>(waveValue);
                }

                this->analogCallback.RenderDiscrete(dingSamples);

                // Prepare the header for playback of the ding sound
                ZeroMemory(&header, sizeof(header));
                header.lpData = (LPSTR)(&dingSamples[0]);
                header.dwBufferLength = sizeof(dingSamples[0]) * dingSamples.size();

                // Prepare the ding sound buffer
                waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
                waveOutWrite(hWaveOut, &header, sizeof(header));

        

                // Wait for ding sound playback to finish
                waveOutWrite(hWaveOut, &header, sizeof(header));

                // Wait 250ms
                Sleep(250);

                // Unprepare the ding sound buffer
                waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
            }

};

#endif
