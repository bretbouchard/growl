/*
  ==============================================================================

    GrowlProcessor.h
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    Main DSP processor for animal vocal synthesis instrument.
    Integrates all DSP modules into complete synthesis engine.

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "NoiseGenerator.h"
#include "OscillatorBank.h"
#include "ResonanceSystem.h"
#include "DistortionStage.h"
#include "SizeScaler.h"
#include "ModulationSystem.h"

namespace Growl {
namespace DSP {

struct Voice
{
    bool active = false;
    int noteNumber = 0;
    float velocity = 0.0f;
    float age = 0.0f;
};

class GrowlProcessor
{
public:
    GrowlProcessor()
    {
        // Initialize all voices to inactive
        for (auto& voice : voices)
            voice.active = false;
    }

    ~GrowlProcessor() = default;

    void prepare (double sampleRate, int samplesPerBlock)
    {
        modulation.prepare(sampleRate, samplesPerBlock);
        reset();
    }

    void noteOn (int noteNumber, float velocity)
    {
        // Find free voice
        for (auto& voice : voices)
        {
            if (!voice.active)
            {
                voice.active = true;
                voice.noteNumber = noteNumber;
                voice.velocity = velocity;
                voice.age = 0.0f;
                modulation.noteOn();
                break;
            }
        }
    }

    void noteOff (int noteNumber)
    {
        // Find voice and release
        for (auto& voice : voices)
        {
            if (voice.active && voice.noteNumber == noteNumber)
            {
                modulation.noteOff();
                break;
            }
        }
    }

    void processBlock (float* output, int numSamples)
    {
        // Clear output
        juce::FloatVectorOperations::fill(output, 0.0f, numSamples);

        // Process active voices
        for (auto& voice : voices)
        {
            if (voice.active)
            {
                // Generate noise
                noise.processBlock(output, numSamples);

                // Add resonance
                for (int i = 0; i < numSamples; ++i)
                    output[i] = resonance.process(output[i]);

                // Apply distortion
                for (int i = 0; i < numSamples; ++i)
                    output[i] = distortion.process(output[i]);

                voice.age += static_cast<float>(numSamples) / 48000.0f;

                // Voice stealing (oldest voice)
                if (!modulation.isNoteOn() && voice.age > 2.0f)
                {
                    voice.active = false;
                }
            }
        }

        // Process modulation
        modulation.process(numSamples);
    }

    void reset()
    {
        noise.reset();
        resonance.reset();
        distortion.reset();
        modulation.reset();

        for (auto& voice : voices)
        {
            voice.active = false;
            voice.age = 0.0f;
        }
    }

private:
    //==============================================================================
    NoiseGenerator noise;
    OscillatorBank oscBank;
    ResonanceSystem resonance;
    DistortionStage distortion;
    SizeScaler sizeScaler;
    ModulationSystem modulation;

    static constexpr int maxVoices = 16;
    Voice voices[maxVoices];

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrowlProcessor)
};

} // namespace DSP
} // namespace Growl
