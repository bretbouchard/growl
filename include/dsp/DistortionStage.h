/*
  ==============================================================================

    DistortionStage.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Distortion stage for aggressive vocal textures.
    Implements 7 distortion types.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace Growl {
namespace DSP {

class DistortionStage
{
public:
    enum DistortionType
    {
        SoftClip = 0,
        HardClip = 1,
        Waveshape = 2,
        Chebyshev = 3,
        Bitcrush = 4,
        Wavefolder = 5,
        HarmonicBalancer = 6
    };

    DistortionStage()
        : distortionType(SoftClip),
          drive(1.0f),
          warmth(0.5f),
          aggression(0.5f)
    {
    }

    ~DistortionStage() = default;

    void setDistortionType (DistortionType type)
    {
        distortionType = type;
    }

    void setDrive (float newDrive)
    {
        drive = juce::jlimit (0.0f, 10.0f, newDrive);
    }

    void setWarmth (float newWarmth)
    {
        warmth = juce::jlimit (0.0f, 1.0f, newWarmth);
    }

    void setAggression (float newAggression)
    {
        aggression = juce::jlimit (0.0f, 1.0f, newAggression);
    }

    float process (float input) noexcept
    {
        // Apply drive
        float driven = input * drive;

        // Apply distortion
        float distorted = 0.0f;
        switch (distortionType)
        {
            case SoftClip:   distorted = softClip(driven); break;
            case HardClip:   distorted = hardClip(driven); break;
            case Waveshape:  distorted = waveShape(driven); break;
            case Chebyshev:  distorted = chebyshev(driven); break;
            case Bitcrush:   distorted = bitcrush(driven); break;
            case Wavefolder: distorted = waveFolder(driven); break;
            case HarmonicBalancer: distorted = harmonicBalance(driven); break;
        }

        // Blend based on warmth
        float output = distorted * (1.0f - warmth) + input * warmth;

        // Apply aggression (boost highs)
        if (aggression > 0.0f)
        {
            float aggressiveBoost = output * (1.0f + aggression * 0.5f);
            output = juce::jlimit(-1.0f, 1.0f, aggressiveBoost);
        }

        return output;
    }

    void processBlock (float* output, const float* input, int numSamples) noexcept
    {
        for (int i = 0; i < numSamples; ++i)
            output[i] = process(input[i]);
    }

    void reset() noexcept
    {
        // No state to reset
    }

private:
    //==============================================================================
    float softClip (float x) noexcept
    {
        // Soft clipping using tanh
        return std::tanh(x);
    }

    float hardClip (float x) noexcept
    {
        // Hard clipping
        return juce::jlimit(-1.0f, 1.0f, x);
    }

    float waveShape (float x) noexcept
    {
        // Waveshaping using cubic function
        float x2 = x * x;
        float x3 = x2 * x;
        return juce::jlimit(-1.0f, 1.0f, x + 0.3f * x2 + 0.1f * x3);
    }

    float chebyshev (float x) noexcept
    {
        // Chebyshev polynomial (adds harmonics)
        float x2 = x * x;
        float t2 = 2.0f * x2 - 1.0f; // 2nd Chebyshev polynomial
        float t3 = 4.0f * x2 * x - 3.0f * x; // 3rd Chebyshev polynomial
        return 0.5f * x + 0.3f * t2 + 0.2f * t3;
    }

    float bitcrush (float x) noexcept
    {
        // Bitcrushing (quantization)
        float bits = 16.0f - (drive * 14.0f); // 2 to 16 bits
        float levels = std::pow(2.0f, bits);
        float crushed = std::floor(x * levels) / levels;
        return juce::jlimit(-1.0f, 1.0f, crushed);
    }

    float waveFolder (float x) noexcept
    {
        // Wave folding (creates harmonics)
        float threshold = 1.0f / drive;
        if (std::abs(x) < threshold)
            return x;

        float folded = std::fmod(std::abs(x) - threshold, 2.0f * threshold);
        if (folded > threshold)
            folded = 2.0f * threshold - folded;

        return (x < 0.0f ? -1.0f : 1.0f) * folded;
    }

    float harmonicBalance (float x) noexcept
    {
        // Harmonic balancer (even/odd harmonic balance)
        float even = std::cos(x * juce::MathConstants<float>::pi);
        float odd = std::sin(x * juce::MathConstants<float>::pi);
        return (even + odd) * 0.5f;
    }

    //==============================================================================
    DistortionType distortionType;
    float drive;
    float warmth;
    float aggression;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionStage)
};

} // namespace DSP
} // namespace Growl
