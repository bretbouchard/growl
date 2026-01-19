/*
  ==============================================================================

    Preset.h
    Created: 19 Jan 2026 4:00:00pm
    Author:  White Room Audio

    Preset data structure for Growl animal vocal synthesis instrument.

  ==============================================================================
*/

#pragma once

#include <juce_data_structures/juce_data_structures.h>
#include <string>

//==============================================================================
/**
    Noise type enumeration for different noise characteristics
*/
enum class NoiseType
{
    White,           // Flat frequency spectrum
    Pink,            // -3dB/octave (natural)
    Brown,           // -6dB/octave (deep)
    Bandpass,        // Band-limited noise
    PinkMixed        // Pink + white mixture
};

//==============================================================================
/**
    Oscillator type enumeration for different synthesis methods
*/
enum class OscillatorType
{
    Detuned,         // Detuned saw waves
    DPW,             // Differentiated Parabolic Waveforms
    PolyBLEP,        // Polynomial Bandlimited Step
    Wavetable,       // Wavetable synthesis
    Wavefolder       // Wavefolding distortion
};

//==============================================================================
/**
    Distortion type enumeration for harmonic generation
*/
enum class DistortionType
{
    SoftClip,        // Soft clipping (tanh)
    Waveshape,       // Waveshaping distortion
    HarmonicBalancer, // Harmonic balance
    Chebyshev,       // Chebyshev polynomial
    Wavefolder,      // Wavefolding
    Bitcrush         // Bitcrushing
};

//==============================================================================
/**
    Preset parameters structure
*/
struct PresetParameters
{
    // Animal identification
    std::string animalName;
    std::string presetName;

    // Size scaling (inverse square law for acoustic impedance)
    float sizeFeet;                      // Animal size in feet (1.0 to 100.0+)

    // Noise source
    NoiseType noiseType;
    float noiseMix;                      // 0.0 to 1.0

    // Oscillator bank
    OscillatorType oscillatorType;
    float oscillatorDetune;              // Semitones
    float oscillatorMix;                 // 0.0 to 1.0

    // Formant frequencies (vocal tract resonances)
    float formantFreqs[5];               // 5 formant frequencies in Hz
    float formantQs[5];                  // 5 formant Q values (bandwidth)

    // Distortion stage
    DistortionType distortionType;
    float drive;                         // Distortion drive amount
    float tone;                          // Tone control

    // Resonance system
    float chestResonance;                // 0.0 to 1.0
    float throatResonance;               // 0.0 to 1.0
    float resonanceMix;                  // 0.0 to 1.0

    // Master
    float masterGain;                    // dB

    //==============================================================================
    PresetParameters()
        : animalName (""),
          presetName (""),
          sizeFeet (5.0f),
          noiseType (NoiseType::Pink),
          noiseMix (0.5f),
          oscillatorType (OscillatorType::Detuned),
          oscillatorDetune (0.0f),
          oscillatorMix (0.5f),
          distortionType (DistortionType::SoftClip),
          drive (1.5f),
          tone (0.5f),
          chestResonance (0.5f),
          throatResonance (0.5f),
          resonanceMix (0.5f),
          masterGain (0.0f)
    {
        // Default formant frequencies (human-like)
        formantFreqs[0] = 800.0f;
        formantFreqs[1] = 1150.0f;
        formantFreqs[2] = 2900.0f;
        formantFreqs[3] = 3900.0f;
        formantFreqs[4] = 4950.0f;

        // Default formant Q values
        formantQs[0] = 10.0f;
        formantQs[1] = 12.0f;
        formantQs[2] = 15.0f;
        formantQs[3] = 15.0f;
        formantQs[4] = 20.0f;
    }

    //==============================================================================
    /**
        Convert NoiseType to string
    */
    static juce::String noiseTypeToString (NoiseType type)
    {
        switch (type)
        {
            case NoiseType::White:        return "White";
            case NoiseType::Pink:         return "Pink";
            case NoiseType::Brown:        return "Brown";
            case NoiseType::Bandpass:     return "Bandpass";
            case NoiseType::PinkMixed:    return "PinkMixed";
            default:                      return "Pink";
        }
    }

    //==============================================================================
    /**
        Convert string to NoiseType
    */
    static NoiseType stringToNoiseType (const juce::String& str)
    {
        if (str == "White")        return NoiseType::White;
        if (str == "Pink")         return NoiseType::Pink;
        if (str == "Brown")        return NoiseType::Brown;
        if (str == "Bandpass")     return NoiseType::Bandpass;
        if (str == "PinkMixed")    return NoiseType::PinkMixed;
        return NoiseType::Pink;
    }

    //==============================================================================
    /**
        Convert OscillatorType to string
    */
    static juce::String oscillatorTypeToString (OscillatorType type)
    {
        switch (type)
        {
            case OscillatorType::Detuned:     return "Detuned";
            case OscillatorType::DPW:         return "DPW";
            case OscillatorType::PolyBLEP:    return "PolyBLEP";
            case OscillatorType::Wavetable:   return "Wavetable";
            case OscillatorType::Wavefolder:  return "Wavefolder";
            default:                          return "Detuned";
        }
    }

    //==============================================================================
    /**
        Convert string to OscillatorType
    */
    static OscillatorType stringToOscillatorType (const juce::String& str)
    {
        if (str == "Detuned")     return OscillatorType::Detuned;
        if (str == "DPW")         return OscillatorType::DPW;
        if (str == "PolyBLEP")    return OscillatorType::PolyBLEP;
        if (str == "Wavetable")   return OscillatorType::Wavetable;
        if (str == "Wavefolder")  return OscillatorType::Wavefolder;
        return OscillatorType::Detuned;
    }

    //==============================================================================
    /**
        Convert DistortionType to string
    */
    static juce::String distortionTypeToString (DistortionType type)
    {
        switch (type)
        {
            case DistortionType::SoftClip:          return "SoftClip";
            case DistortionType::Waveshape:         return "Waveshape";
            case DistortionType::HarmonicBalancer:  return "HarmonicBalancer";
            case DistortionType::Chebyshev:         return "Chebyshev";
            case DistortionType::Wavefolder:        return "Wavefolder";
            case DistortionType::Bitcrush:          return "Bitcrush";
            default:                                return "SoftClip";
        }
    }

    //==============================================================================
    /**
        Convert string to DistortionType
    */
    static DistortionType stringToDistortionType (const juce::String& str)
    {
        if (str == "SoftClip")          return DistortionType::SoftClip;
        if (str == "Waveshape")         return DistortionType::Waveshape;
        if (str == "HarmonicBalancer")  return DistortionType::HarmonicBalancer;
        if (str == "Chebyshev")         return DistortionType::Chebyshev;
        if (str == "Wavefolder")        return DistortionType::Wavefolder;
        if (str == "Bitcrush")          return DistortionType::Bitcrush;
        return DistortionType::SoftClip;
    }

    //==============================================================================
    /**
        Serialize preset to XML
    */
    juce::ValueTree toValueTree() const
    {
        juce::ValueTree preset ("preset");

        preset.setProperty ("animalName", juce::String (animalName), nullptr);
        preset.setProperty ("presetName", juce::String (presetName), nullptr);
        preset.setProperty ("sizeFeet", sizeFeet, nullptr);
        preset.setProperty ("noiseType", noiseTypeToString (noiseType), nullptr);
        preset.setProperty ("noiseMix", noiseMix, nullptr);
        preset.setProperty ("oscillatorType", oscillatorTypeToString (oscillatorType), nullptr);
        preset.setProperty ("oscillatorDetune", oscillatorDetune, nullptr);
        preset.setProperty ("oscillatorMix", oscillatorMix, nullptr);
        preset.setProperty ("distortionType", distortionTypeToString (distortionType), nullptr);
        preset.setProperty ("drive", drive, nullptr);
        preset.setProperty ("tone", tone, nullptr);
        preset.setProperty ("chestResonance", chestResonance, nullptr);
        preset.setProperty ("throatResonance", throatResonance, nullptr);
        preset.setProperty ("resonanceMix", resonanceMix, nullptr);
        preset.setProperty ("masterGain", masterGain, nullptr);

        // Formant frequencies
        juce::ValueTree formants ("formants");
        for (int i = 0; i < 5; ++i)
        {
            juce::ValueTree formant ("formant");
            formant.setProperty ("index", i, nullptr);
            formant.setProperty ("freq", formantFreqs[i], nullptr);
            formant.setProperty ("q", formantQs[i], nullptr);
            formants.addChild (formant, -1, nullptr);
        }
        preset.addChild (formants, -1, nullptr);

        return preset;
    }

    //==============================================================================
    /**
        Deserialize preset from XML
    */
    static PresetParameters fromValueTree (const juce::ValueTree& preset)
    {
        PresetParameters params;

        params.animalName = preset.getProperty ("animalName").toString().toStdString();
        params.presetName = preset.getProperty ("presetName").toString().toStdString();
        params.sizeFeet = preset.getProperty ("sizeFeet", 5.0f);
        params.noiseType = stringToNoiseType (preset.getProperty ("noiseType", "Pink").toString());
        params.noiseMix = preset.getProperty ("noiseMix", 0.5f);
        params.oscillatorType = stringToOscillatorType (preset.getProperty ("oscillatorType", "Detuned").toString());
        params.oscillatorDetune = preset.getProperty ("oscillatorDetune", 0.0f);
        params.oscillatorMix = preset.getProperty ("oscillatorMix", 0.5f);
        params.distortionType = stringToDistortionType (preset.getProperty ("distortionType", "SoftClip").toString());
        params.drive = preset.getProperty ("drive", 1.5f);
        params.tone = preset.getProperty ("tone", 0.5f);
        params.chestResonance = preset.getProperty ("chestResonance", 0.5f);
        params.throatResonance = preset.getProperty ("throatResonance", 0.5f);
        params.resonanceMix = preset.getProperty ("resonanceMix", 0.5f);
        params.masterGain = preset.getProperty ("masterGain", 0.0f);

        // Formant frequencies
        juce::ValueTree formants = preset.getChildWithName ("formants");
        if (formants.isValid())
        {
            for (int i = 0; i < 5 && i < formants.getNumChildren(); ++i)
            {
                juce::ValueTree formant = formants.getChild (i);
                params.formantFreqs[i] = formant.getProperty ("freq", 800.0f);
                params.formantQs[i] = formant.getProperty ("q", 10.0f);
            }
        }

        return params;
    }
};
