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

//==============================================================================
class GrowlPlugin  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GrowlPlugin()
        : AudioProcessor (BusesProperties()
                           .withInput ("Input",  juce::AudioChannelSet::stereo())
                           .withOutput ("Output", juce::AudioChannelSet::stereo()))
    {
    }

    ~GrowlPlugin() override = default;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        // Prepare DSP modules here
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

        // Process audio
        // TODO: Add actual DSP processing here
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
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool producesMidi() const override
    {
        #if JucePlugin_ProducesMidiOutput
            return true;
        #else
            return false;
        #endif
    }

    double getTailLengthSeconds() const override
    {
        return 0.0;
    }

    //==============================================================================
    int getNumPrograms() override
    {
        return 1; // TODO: 50 presets when implemented
    }

    int getCurrentProgram() override
    {
        return 0;
    }

    void setCurrentProgram (int index) override
    {
        juce::ignoreUnused (index);
    }

    const juce::String getProgramName (int index) override
    {
        juce::ignoreUnused (index);
        return "Default";
    }

    void changeProgramName (int index, const juce::String& newName) override
    {
        juce::ignoreUnused (index, newName);
    }

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override
    {
        // Save state
        juce::ignoreUnused (destData);
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        // Restore state
        juce::ignoreUnused (data, sizeInBytes);
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrowlPlugin)
};

//==============================================================================
// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GrowlPlugin();
}
