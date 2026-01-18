/*
  ==============================================================================

    OscillatorBank.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Oscillator bank for animal vocal synthesis.
    Implements 4 oscillator types: DPW, PolyBLEP, Wavetable, Detuned.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <random>
#include <vector>

namespace Growl {
namespace DSP {

class OscillatorBank
{
public:
    enum OscillatorType
    {
        DPW = 0,         // Differentiated Parabolic Waveform
        PolyBLEP = 1,    // Polynomial Bandlimited Steep
        Wavetable = 2,   // Wavetable synthesis
        Detuned = 3      // Detuned sawtooth bank
    };

    OscillatorBank()
        : oscType(DPW),
          sampleRate(48000.0),
          phase(0.0f),
          frequency(440.0f),
          detuneAmount(0.0f),
          numVoices(4)
    {
    }

    ~OscillatorBank() = default;

    void setOscillatorType (OscillatorType type)
    {
        oscType = type;
    }

    void setFrequency (float freq)
    {
        frequency = juce::jlimit (20.0f, 20000.0f, freq);
    }

    void setDetune (float detune)
    {
        detuneAmount = juce::jlimit (-100.0f, 100.0f, detune);
    }

    void setNumVoices (int voices)
    {
        numVoices = juce::jlimit (1, 16, voices);
    }

    float process() noexcept
    {
        switch (oscType)
        {
            case DPW: return processDPW();
            case PolyBLEP: return processPolyBLEP();
            case Wavetable: return processWavetable();
            case Detuned: return processDetuned();
            default: return processDPW();
        }
    }

    void processBlock (float* output, int numSamples) noexcept
    {
        for (int i = 0; i < numSamples; ++i)
            output[i] = process();
    }

    void reset() noexcept
    {
        phase = 0.0f;
    }

private:
    //==============================================================================
    float processDPW() noexcept
    {
        // Differentiated Parabolic Waveform - bandlimited sawtooth
        float t = phase;
        float saw = 2.0f * t - 1.0f;
        float dpw = saw - saw * saw; // Parabolic transform

        // Differentiate (simple difference)
        static float lastSample = 0.0f;
        float output = dpw - lastSample;
        lastSample = dpw;

        // Update phase
        phase += frequency / static_cast<float>(sampleRate);
        if (phase >= 1.0f) phase -= 1.0f;

        return output * 4.0f; // Normalize
    }

    float processPolyBLEP() noexcept
    {
        // Simplified PolyBLEP (bandlimited step function)
        float t = phase;
        float saw = 2.0f * t - 1.0f;

        // Naive BLEP correction at discontinuity
        float blep = 0.0f;
        if (phase < 0.1f)
        {
            float x = phase / 0.1f;
            blep = x * x * (3.0f - 2.0f * x); // Smoothstep
        }

        // Update phase
        phase += frequency / static_cast<float>(sampleRate);
        if (phase >= 1.0f) phase -= 1.0f;

        return saw + blep * 0.1f;
    }

    float processWavetable() noexcept
    {
        // Simple wavetable with sine + harmonics
        float t = phase * 2.0f * juce::MathConstants<float>::pi;
        float output = std::sin(t);
        output += 0.5f * std::sin(2.0f * t);
        output += 0.25f * std::sin(3.0f * t);
        output += 0.125f * std::sin(4.0f * t);

        // Normalize
        output /= 1.875f;

        // Update phase
        phase += frequency / static_cast<float>(sampleRate);
        if (phase >= 1.0f) phase -= 1.0f;

        return output;
    }

    float processDetuned() noexcept
    {
        // Detuned sawtooth bank
        float output = 0.0f;

        for (int i = 0; i < numVoices; ++i)
        {
            float detune = (static_cast<float>(i) - static_cast<float>(numVoices) * 0.5f) * detuneAmount;
            float detuneFreq = frequency * std::pow(2.0f, detune / 1200.0f); // Cents

            float t = phase + static_cast<float>(i) * 0.01f; // Phase offset
            float saw = 2.0f * t - 1.0f;
            output += saw;
        }

        output /= static_cast<float>(numVoices);

        // Update phase
        phase += frequency / static_cast<float>(sampleRate);
        if (phase >= 1.0f) phase -= 1.0f;

        return output;
    }

    //==============================================================================
    OscillatorType oscType;
    double sampleRate;
    float phase;
    float frequency;
    float detuneAmount;
    int numVoices;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorBank)
};

} // namespace DSP
} // namespace Growl
