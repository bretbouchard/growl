/*
  ==============================================================================

    ResonanceSystem.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Formant-based resonance system for animal vocal synthesis.
    Implements 5 parallel formant filters with size scaling.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace Growl {
namespace DSP {

class ResonanceSystem
{
public:
    ResonanceSystem()
        : sampleRate(48000.0),
          chestResonance(0.6f),
          throatConstriction(0.4f)
    {
        // Default formant frequencies (Hz) - typical lion growl
        float defaultFreqs[5] = {200.0f, 440.0f, 800.0f, 1500.0f, 2500.0f};
        float defaultQs[5] = {8.0f, 8.0f, 6.0f, 5.0f, 4.0f};

        for (int i = 0; i < numFormants; ++i)
        {
            formantFreqs[i] = defaultFreqs[i];
            formantQs[i] = defaultQs[i];
            formantStates[i] = {0.0f, 0.0f, 0.0f, 0.0f};
        }
    }

    ~ResonanceSystem() = default;

    void setChestResonance (float mix)
    {
        chestResonance = juce::jlimit (0.0f, 1.0f, mix);
    }

    void setThroatConstriction (float constriction)
    {
        throatConstriction = juce::jlimit (0.0f, 1.0f, constriction);
    }

    void setFormantFrequency (int index, float freq)
    {
        if (index >= 0 && index < numFormants)
            formantFreqs[index] = juce::jlimit (50.0f, 10000.0f, freq);
    }

    void setFormantQ (int index, float q)
    {
        if (index >= 0 && index < numFormants)
            formantQs[index] = juce::jlimit (1.0f, 20.0f, q);
    }

    float process (float input) noexcept
    {
        float output = 0.0f;

        // Process through all 5 formant filters
        for (int i = 0; i < numFormants; ++i)
        {
            float formantOutput = processFormant(input, i);
            output += formantOutput * formantGains[i];
        }

        output /= static_cast<float>(numFormants);

        // Mix chest and throat resonance
        float chest = output * chestResonance;
        float throat = output * (1.0f - chestResonance);

        // Apply throat constriction (boosts higher formants)
        throat *= (1.0f + throatConstriction * 0.5f);

        return chest + throat;
    }

    void processBlock (float* output, const float* input, int numSamples) noexcept
    {
        for (int i = 0; i < numSamples; ++i)
            output[i] = process(input[i]);
    }

    void reset() noexcept
    {
        for (auto& state : formantStates)
        {
            state.x1 = state.x2 = state.y1 = state.y2 = 0.0f;
        }
    }

private:
    //==============================================================================
    float processFormant (float input, int index) noexcept
    {
        auto& state = formantStates[index];
        float freq = formantFreqs[index];
        float Q = formantQs[index];

        // Calculate bandpass coefficients
        float omega = 2.0f * juce::MathConstants<float>::pi * freq / static_cast<float>(sampleRate);
        float alpha = std::sin(omega) / (2.0f * Q);

        float b0 = alpha;
        float b1 = 0.0f;
        float b2 = -alpha;
        float a0 = 1.0f + alpha;
        float a1 = -2.0f * std::cos(omega);
        float a2 = 1.0f - alpha;

        // Normalize
        b0 /= a0;
        b1 /= a0;
        b2 /= a0;
        a1 /= a0;
        a2 /= a0;

        // Biquad difference equation
        float output = b0 * input + b1 * state.x1 + b2 * state.x2 - a1 * state.y1 - a2 * state.y2;

        state.x2 = state.x1;
        state.x1 = input;
        state.y2 = state.y1;
        state.y1 = output;

        return output;
    }

    //==============================================================================
    static constexpr int numFormants = 5;

    struct FormantState
    {
        float x1, x2, y1, y2;
    };

    double sampleRate;
    float chestResonance;
    float throatConstriction;
    float formantFreqs[numFormants];
    float formantQs[numFormants];
    float formantGains[numFormants] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    FormantState formantStates[numFormants];

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResonanceSystem)
};

} // namespace DSP
} // namespace Growl
