/*
  ==============================================================================

    GrowlPlugin.cpp
    Created: 18 Jan 2026 2:30:00pm
    Author:  White Room Audio

    JUCE AudioProcessor wrapper for Growl animal vocal synthesis instrument.

  ==============================================================================
*/

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "dsp/Preset.h"
#include "dsp/FactoryPresets.h"
#include "dsp/SizeScaler.h"
#include "dsp/NoiseGenerator.h"
#include "dsp/OscillatorBank.h"
#include "dsp/ResonanceSystem.h"
#include "dsp/DistortionStage.h"

//==============================================================================
class GrowlPlugin  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GrowlPlugin()
        : AudioProcessor (BusesProperties()
                           .withInput ("Input",  juce::AudioChannelSet::stereo())
                           .withOutput ("Output",  juce::AudioChannelSet::stereo())),
          currentPresetIndex (0),
          sampleRate (48000.0)
    {
        // Load all factory presets
        loadFactoryPresets();

        // Initialize DSP modules with default preset
        if (!factoryPresets.empty())
        {
            currentPreset = factoryPresets[0];
        }
    }

    ~GrowlPlugin() override = default;

    //==============================================================================
    void prepareToPlay (double newSampleRate, int samplesPerBlock) override
    {
        sampleRate = newSampleRate;

        // Prepare DSP modules
        sizeScaler.prepare (sampleRate);
        noiseGenerator.prepare (sampleRate);
        oscillatorBank.prepare (sampleRate);
        resonanceSystem.prepare (sampleRate);
        distortionStage.prepare (sampleRate);

        juce::ignoreUnused (samplesPerBlock);
    }

    void releaseResources() override
    {
        // Free DSP resources here
    }

    void processBlock (juce::AudioBuffer<float>& buffer,
                       juce::MidiBuffer& midiMessages) override
    {
        juce::ScopedNoDenormals noDenormals;
        auto totalNumInputChannels  = getTotalNumInputChannels();
        auto totalNumOutputChannels = getTotalNumOutputChannels();

        // Clear output buffer
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());

        // DSP Pipeline: NoiseGenerator -> OscillatorBank -> Mix -> ResonanceSystem -> DistortionStage
        auto numSamples = buffer.getNumSamples();

        // Process MIDI for note triggers
        for (const auto metadata : midiMessages)
        {
            const auto message = metadata.getMessage();
            if (message.isNoteOn())
            {
                // Trigger oscillator bank with MIDI note
                auto midiNote = message.getNoteNumber();
                auto frequency = 440.0 * std::pow(2.0, (midiNote - 69) / 12.0);
                oscillatorBank.setFrequency(frequency);
                oscillatorBank.setGate(true);
            }
            else if (message.isNoteOff())
            {
                oscillatorBank.setGate(false);
            }
        }

        // Get output channel (mono to stereo)
        auto* outputLeft = buffer.getWritePointer(0);
        auto* outputRight = buffer.getWritePointer(1);

        // Process each sample
        for (int sample = 0; sample < numSamples; ++sample)
        {
            // 1. Generate noise component
            float noise = noiseGenerator.process();

            // 2. Generate oscillator component
            float oscillator = oscillatorBank.process();

            // 3. Mix noise and oscillators based on preset
            float mixed = (noise * (1.0f - currentPreset.oscillatorMix)) +
                         (oscillator * currentPreset.oscillatorMix);

            // 4. Apply resonance system (formants)
            float resonant = resonanceSystem.process(mixed);

            // 5. Apply distortion
            float distorted = distortionStage.process(resonant);

            // 6. Apply master gain
            float output = distorted * currentPreset.masterGain;

            // Write to output buffer (mono to stereo)
            outputLeft[sample] = output;
            if (totalNumOutputChannels > 1)
                outputRight[sample] = output;
        }

        // Clear remaining channels if any
        for (int channel = 2; channel < totalNumOutputChannels; ++channel)
            buffer.clear(channel, 0, numSamples);
    }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override
    {
        return nullptr; // No editor for now
    }

    bool hasEditor() const override
    {
        return false; // TODO: true when editor is implemented
    }

    //==============================================================================
    const juce::String getName() const override
    {
        return "Growl";
    }

    bool acceptsMidi() const override
    {
        return true;
    }

    bool producesMidi() const override
    {
        return false;
    }

    double getTailLengthSeconds() const override
    {
        return 0.0;
    }

    //==============================================================================
    int getNumPrograms() override
    {
        return static_cast<int> (factoryPresets.size());
    }

    int getCurrentProgram() override
    {
        return currentPresetIndex;
    }

    void setCurrentProgram (int index) override
    {
        if (juce::isPositiveAndBelow (index, static_cast<int> (factoryPresets.size())))
        {
            currentPresetIndex = index;
            currentPreset = factoryPresets[index];
            applyPresetToDSP();
        }
    }

    const juce::String getProgramName (int index) override
    {
        if (juce::isPositiveAndBelow (index, static_cast<int> (factoryPresets.size())))
            return factoryPresets[index].presetName;

        return {};
    }

    void changeProgramName (int index, const juce::String& newName) override
    {
        if (juce::isPositiveAndBelow (index, static_cast<int> (factoryPresets.size())))
            factoryPresets[index].presetName = newName.toStdString();
    }

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override
    {
        // Save current preset state
        juce::ValueTree state ("state");
        state.setProperty ("currentPreset", currentPresetIndex, nullptr);

        // Convert current preset to XML
        juce::ValueTree presetTree = currentPreset.toValueTree();
        state.addChild (presetTree, -1, nullptr);

        // Copy to memory block
        juce::MemoryOutputStream stream (destData, false);
        state.writeToStream (stream);
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        // Restore preset state
        juce::MemoryInputStream stream (data, static_cast<std::size_t> (sizeInBytes), false);
        juce::ValueTree state = juce::ValueTree::readFromStream (stream);

        if (state.isValid())
        {
            currentPresetIndex = state.getProperty ("currentPreset", 0);

            juce::ValueTree presetTree = state.getChildWithName ("preset");
            if (presetTree.isValid())
            {
                currentPreset = PresetParameters::fromValueTree (presetTree);
                applyPresetToDSP();
            }
        }
    }

private:
    //==============================================================================
    /**
        Load all factory presets from the embedded preset data
    */
    void loadFactoryPresets()
    {
        factoryPresets.clear();

        // Load all 50 factory presets from FactoryPresets class
        factoryPresets = FactoryPresets::getAllPresets();

        // Verify we loaded all 50 presets
        jassert (factoryPresets.size() == 50);
    }

    //==============================================================================
    /**
        Apply current preset parameters to all DSP modules
    */
    void applyPresetToDSP()
    {
        // 1. Apply size scaling
        sizeScaler.setSizeFeet (currentPreset.sizeFeet);
        sizeScaler.setScalingType (Growl::DSP::SizeScaler::Allometric);

        // 2. Apply noise settings
        noiseGenerator.setType (static_cast<int> (currentPreset.noiseType));
        noiseGenerator.setMix (currentPreset.noiseMix);

        // 3. Apply oscillator settings
        oscillatorBank.setType (static_cast<int> (currentPreset.oscillatorType));
        oscillatorBank.setDetune (currentPreset.oscillatorDetune);
        oscillatorBank.setMix (currentPreset.oscillatorMix);

        // 4. Apply formant settings (with size scaling)
        auto formantMult = sizeScaler.getFormantMultiplier();
        for (int i = 0; i < 5; ++i)
        {
            auto scaledFreq = currentPreset.formantFreqs[i] * formantMult;
            resonanceSystem.setFormant (i, scaledFreq, currentPreset.formantQs[i]);
        }
        resonanceSystem.setChestResonance (currentPreset.chestResonance);
        resonanceSystem.setThroatResonance (currentPreset.throatResonance);
        resonanceSystem.setMix (currentPreset.resonanceMix);

        // 5. Apply distortion settings
        distortionStage.setType (static_cast<int> (currentPreset.distortionType));
        distortionStage.setDrive (currentPreset.drive);
        distortionStage.setTone (currentPreset.tone);
    }

    //==============================================================================
    // DSP module instances - fully integrated
    Growl::DSP::SizeScaler sizeScaler;
    Growl::DSP::NoiseGenerator noiseGenerator;
    Growl::DSP::OscillatorBank oscillatorBank;
    Growl::DSP::ResonanceSystem resonanceSystem;
    Growl::DSP::DistortionStage distortionStage;

    // Preset management
    std::vector<PresetParameters> factoryPresets;
    PresetParameters currentPreset;
    int currentPresetIndex;
    double sampleRate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrowlPlugin)
};

//==============================================================================
// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GrowlPlugin();
}
