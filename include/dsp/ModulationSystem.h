/*
  ==============================================================================

    ModulationSystem.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    LFOs and envelope for parameter modulation in animal vocal synthesis.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace Growl {
namespace DSP {

struct LFO
{
    float rate = 1.0f;
    int waveform = 0;
    float depth = 0.5f;
    float phase = 0.0f;
    float bipolar = 1.0f;
    float output = 0.0f;

    enum WaveformType { Sine = 0, Triangle = 1, SawUp = 2, SawDown = 3, Square = 4, SampleHold = 5, Noise = 6 };
};

class ModulationSystem
{
public:
    ModulationSystem()
    {
        for (auto& lfo : lfos)
        {
            lfo.rate = 1.0f;
            lfo.waveform = LFO::Sine;
            lfo.depth = 0.5f;
            lfo.phase = 0.0f;
            lfo.bipolar = 1.0f;
            lfo.output = 0.0f;
        }
    }

    ~ModulationSystem() = default;

    void prepare (double sr, int samplesPerBlock)
    {
        sampleRate = sr;
        inverseSampleRate = 1.0f / static_cast<float>(sampleRate);
    }

    void setLFORate (int lfoIndex, float rateHz)
    {
        if (lfoIndex >= 0 && lfoIndex < 4)
            lfos[lfoIndex].rate = juce::jlimit(0.01f, 100.0f, rateHz);
    }

    void noteOn()
    {
        envStage = 0; // Attack
        envPhase = 0.0f;
    }

    void noteOff()
    {
        envStage = 3; // Release
        envPhase = 0.0f;
    }

    float getLFOOutput (int lfoIndex) const
    {
        if (lfoIndex >= 0 && lfoIndex < 4)
            return lfos[lfoIndex].output;
        return 0.0f;
    }

    float getEnvelopeOutput() const
    {
        return envCurrent;
    }

    void process (int numSamples)
    {
        // Process all LFOs
        for (auto& lfo : lfos)
        {
            float phaseIncrement = lfo.rate * inverseSampleRate * static_cast<float>(numSamples);
            lfo.phase += phaseIncrement;
            while (lfo.phase >= 1.0f)
                lfo.phase -= 1.0f;

            // Generate sine wave
            lfo.output = std::sin(lfo.phase * juce::MathConstants<float>::twoPi) * lfo.depth;
        }

        // Process envelope (simplified ADSR)
        processEnvelope(numSamples);
    }

    void reset()
    {
        for (auto& lfo : lfos)
        {
            lfo.phase = 0.0f;
            lfo.output = 0.0f;
        }
        envCurrent = 0.0f;
        envStage = 4; // Idle
    }

private:
    //==============================================================================
    void processEnvelope (int numSamples)
    {
        float attack = 0.01f;
        float decay = 0.1f;
        float sustain = 0.7f;
        float release = 0.2f;

        float increment = 0.0f;

        switch (envStage)
        {
            case 0: // Attack
                increment = static_cast<float>(numSamples * inverseSampleRate) / attack;
                envCurrent += increment;
                if (envCurrent >= 1.0f)
                {
                    envCurrent = 1.0f;
                    envStage = 1;
                }
                break;

            case 1: // Decay
                increment = static_cast<float>(numSamples * inverseSampleRate) / decay;
                envCurrent -= increment * (1.0f - sustain);
                if (envCurrent <= sustain)
                {
                    envCurrent = sustain;
                    envStage = 2;
                }
                break;

            case 2: // Sustain
                envCurrent = sustain;
                break;

            case 3: // Release
                increment = static_cast<float>(numSamples * inverseSampleRate) / release;
                envCurrent -= increment * sustain;
                if (envCurrent <= 0.0f)
                {
                    envCurrent = 0.0f;
                    envStage = 4;
                }
                break;

            case 4: // Idle
                envCurrent = 0.0f;
                break;
        }

        envCurrent = juce::jlimit(0.0f, 1.0f, envCurrent);
    }

    //==============================================================================
    std::array<LFO, 4> lfos;
    double sampleRate = 44100.0;
    float inverseSampleRate = 1.0f / 44100.0f;
    float envCurrent = 0.0f;
    float envPhase = 0.0f;
    int envStage = 4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationSystem)
};

} // namespace DSP
} // namespace Growl
