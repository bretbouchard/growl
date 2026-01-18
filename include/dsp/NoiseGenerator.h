/*
  ==============================================================================

    NoiseGenerator.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Noise generation for animal vocal synthesis.
    Implements 6 noise types: White, Pink, Brown, Bandpass, PinkMixed, CustomMix.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace Growl {
namespace DSP {

class NoiseGenerator
{
public:
    enum NoiseType
    {
        White = 0,
        Pink = 1,
        Brown = 2,
        Bandpass = 3,
        PinkMixed = 4,
        CustomMix = 5
    };

    NoiseGenerator()
        : noiseType(White)
    {
    }

    ~NoiseGenerator() = default;

    void setNoiseType (NoiseType type)
    {
        noiseType = type;
    }

    float process() noexcept
    {
        switch (noiseType)
        {
            case White: return whiteNoise.process();
            case Pink: return pinkNoise.process();
            case Brown: return brownNoise.process();
            case Bandpass: return bandpassNoise.process();
            case PinkMixed: return (pinkNoise.process() * 0.7f + whiteNoise.process() * 0.3f);
            case CustomMix: return (whiteNoise.process() * 0.5f + pinkNoise.process() * 0.3f + brownNoise.process() * 0.2f);
            default: return whiteNoise.process();
        }
    }

    void processBlock (float* output, int numSamples) noexcept
    {
        for (int i = 0; i < numSamples; ++i)
            output[i] = process();
    }

    void reset() noexcept
    {
        whiteNoise.reset();
        pinkNoise.reset();
        brownNoise.reset();
        bandpassNoise.reset();
    }

private:
    //==============================================================================
    class WhiteNoise
    {
    public:
        WhiteNoise() : state(123456789) {}

        inline float process() noexcept
        {
            state ^= state << 13;
            state ^= state >> 17;
            state ^= state << 5;
            return (float)(state & 0x7FFFFFFF) / (float)0x7FFFFFFF * 2.0f - 1.0f;
        }

        void reset() noexcept { state = 123456789; }

    private:
        uint32_t state;
    };

    class PinkNoise
    {
    public:
        PinkNoise()
        {
            for (auto& s : state) s = 0;
            counter = 0;
        }

        inline float process() noexcept
        {
            counter++;
            int roll = counter % 5;

            for (int i = 0; i < 5; ++i)
            {
                if (roll % 2 == 1)
                {
                    state[i] -= (state[i] >> 1);
                    state[i] += (rand() & 0x7FFFFFFF) >> 1;
                }
                roll >>= 1;
            }

            float sum = state[0] + state[1] + state[2] + state[3] + state[4];
            return sum / 161430000.0f * 2.0f - 1.0f;
        }

        void reset() noexcept
        {
            for (auto& s : state) s = 0;
            counter = 0;
        }

    private:
        int state[5];
        int counter;
    };

    class BrownNoise
    {
    public:
        BrownNoise() : lastValue(0.0f) {}

        inline float process() noexcept
        {
            float white = (float)(rand() & 0x7FFFFFFF) / (float)0x7FFFFFFF * 2.0f - 1.0f;
            lastValue = (lastValue + (0.02f * white)) / 1.02f;
            lastValue = juce::jlimit (-1.0f, 1.0f, lastValue);
            return lastValue;
        }

        void reset() noexcept { lastValue = 0.0f; }

    private:
        float lastValue;
    };

    class BandpassNoise
    {
    public:
        BandpassNoise() : x1(0.0f), x2(0.0f), y1(0.0f), y2(0.0f) {}

        inline float process() noexcept
        {
            float input = (float)(rand() & 0x7FFFFFFF) / (float)0x7FFFFFFF * 2.0f - 1.0f;

            // Simple bandpass filter (300-3000 Hz for vocal range)
            float output = 0.5f * input - 0.5f * x2 + 0.95f * y1;
            x2 = x1;
            x1 = input;
            y1 = output;

            return juce::jlimit (-1.0f, 1.0f, output);
        }

        void reset() noexcept { x1 = x2 = y1 = y2 = 0.0f; }

    private:
        float x1, x2, y1, y2;
    };

    //==============================================================================
    WhiteNoise whiteNoise;
    PinkNoise pinkNoise;
    BrownNoise brownNoise;
    BandpassNoise bandpassNoise;
    NoiseType noiseType;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGenerator)
};

} // namespace DSP
} // namespace Growl
