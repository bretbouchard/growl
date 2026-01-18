/*
  ==============================================================================

    SizeScaler.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Physical modeling of animal size affecting pitch, formants, and timbre.
    Implements 6 scaling formulas for different animal types.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace Growl {
namespace DSP {

class SizeScaler
{
public:
    enum ScalingType
    {
        Linear = 0,
        Logarithmic = 1,
        Exponential = 2,
        Allometric = 3,
        Frequency = 4,
        Custom = 5
    };

    SizeScaler()
        : currentSize(10.0f),
          scalingType(Allometric)
    {
        updateMultipliers();
    }

    ~SizeScaler() = default;

    void setSizeFeet (float size)
    {
        currentSize = juce::jlimit (1.0f, 10000.0f, size);
        updateMultipliers();
    }

    void setScalingType (ScalingType type)
    {
        scalingType = type;
        updateMultipliers();
    }

    float getPitchMultiplier() const
    {
        return pitchMultiplier;
    }

    float getFormantMultiplier() const
    {
        return formantMultiplier;
    }

    float getResonanceMultiplier() const
    {
        return resonanceMultiplier;
    }

    float getBrightnessMultiplier() const
    {
        return brightnessMultiplier;
    }

private:
    //==============================================================================
    void updateMultipliers()
    {
        float scale = 1.0f;

        switch (scalingType)
        {
            case Linear:       scale = calculateLinearScale(); break;
            case Logarithmic:  scale = calculateLogScale(); break;
            case Exponential:  scale = calculateExpScale(); break;
            case Allometric:   scale = calculateAllometricScale(); break;
            case Frequency:    scale = calculateFrequencyScale(); break;
            case Custom:       scale = 1.0f; break;
        }

        pitchMultiplier = scale;
        formantMultiplier = std::pow(scale, 0.8f);
        resonanceMultiplier = std::sqrt(scale);
        brightnessMultiplier = 1.0f / std::sqrt(scale);
    }

    float calculateLinearScale() const
    {
        return currentSize / 10.0f;
    }

    float calculateLogScale() const
    {
        return std::log2(juce::jmax(1.0f, currentSize / 5.0f));
    }

    float calculateExpScale() const
    {
        auto normalizedSize = currentSize / 10.0f;
        return std::pow(normalizedSize, -0.5f);
    }

    float calculateAllometricScale() const
    {
        auto normalizedSize = currentSize / 10.0f;
        return std::pow(normalizedSize, -1.0f);
    }

    float calculateFrequencyScale() const
    {
        auto normalizedSize = currentSize / 10.0f;
        return std::pow(normalizedSize, -0.8f);
    }

    //==============================================================================
    float currentSize;
    ScalingType scalingType;
    float pitchMultiplier = 1.0f;
    float formantMultiplier = 1.0f;
    float resonanceMultiplier = 1.0f;
    float brightnessMultiplier = 1.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SizeScaler)
};

} // namespace DSP
} // namespace Growl
