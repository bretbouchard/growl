# Growl Instrument - DSP Integration Guide

## Overview

This guide explains how to integrate the 50 factory presets into the actual DSP modules for the Growl animal vocal synthesis instrument.

## Current Status

✅ **Complete:**
- Preset data structure (`Preset.h`)
- All 50 factory presets (`FactoryPresets.cpp`)
- Plugin wrapper integration (`GrowlPlugin.cpp`)
- CMakeLists.txt updated

⏳ **Pending:**
- DSP module parameter integration
- Audio quality testing
- CPU performance validation

## DSP Module Integration

### 1. SizeScaler Integration

**File:** `include/dsp/SizeScaler.h`

**Preset Parameters to Apply:**
```cpp
// From PresetParameters
sizeFeet           // Animal size in feet (1.0 to 100.0+)
```

**Integration Code:**
```cpp
// In GrowlPlugin::prepareToPlay() or preset loading
sizeScaler.setSizeFeet (currentPreset.sizeFeet);
sizeScaler.setScalingType (Growl::DSP::SizeScaler::Allometric);

// Then use the multipliers in processBlock():
auto pitchMult = sizeScaler.getPitchMultiplier();
auto formantMult = sizeScaler.getFormantMultiplier();
auto resonanceMult = sizeScaler.getResonanceMultiplier();
```

**What It Does:**
- Applies inverse square law scaling
- Larger animals → lower pitch, lower formants
- Smaller animals → higher pitch, higher formants

### 2. NoiseGenerator Integration

**File:** `include/dsp/NoiseGenerator.h`

**Preset Parameters to Apply:**
```cpp
// From PresetParameters
noiseType         // NoiseType enum (White, Pink, Brown, Bandpass, PinkMixed)
noiseMix          // 0.0 to 1.0 (noise vs oscillator mix)
```

**Integration Code:**
```cpp
// Apply preset parameters
noiseGenerator.setType (static_cast<int> (currentPreset.noiseType));
noiseGenerator.setMix (currentPreset.noiseMix);

// In processBlock():
auto noise = noiseGenerator.process(); // Returns noise buffer
```

**What It Does:**
- Generates different noise colors
- Mixes between noise and tonal components
- Provides the "breath" and "grit" in animal vocalizations

### 3. OscillatorBank Integration

**File:** `include/dsp/OscillatorBank.h`

**Preset Parameters to Apply:**
```cpp
// From PresetParameters
oscillatorType    // OscillatorType enum (Detuned, DPW, PolyBLEP, Wavetable, Wavefolder)
oscillatorDetune  // Detuning in semitones
oscillatorMix     // 0.0 to 1.0 (oscillator vs noise mix)
```

**Integration Code:**
```cpp
// Apply preset parameters
oscillatorBank.setType (static_cast<int> (currentPreset.oscillatorType));
oscillatorBank.setDetune (currentPreset.oscillatorDetune);
oscillatorBank.setMix (currentPreset.oscillatorMix);

// Apply size scaling to oscillator pitch
auto scaledPitch = basePitch * sizeScaler.getPitchMultiplier();
oscillatorBank.setPitch (scaledPitch);

// In processBlock():
auto osc = oscillatorBank.process(); // Returns oscillator buffer
```

**What It Does:**
- Generates the tonal core of the sound
- Different oscillator types provide different harmonic content
- Detuning creates richness and movement

### 4. ResonanceSystem Integration

**File:** `include/dsp/ResonanceSystem.h`

**Preset Parameters to Apply:**
```cpp
// From PresetParameters
formantFreqs[5]   // 5 formant frequencies in Hz
formantQs[5]      // 5 formant Q values (bandwidth)
chestResonance    // 0.0 to 1.0 (chest resonance amount)
throatResonance   // 0.0 to 1.0 (throat resonance amount)
resonanceMix      // 0.0 to 1.0 (overall resonance mix)
```

**Integration Code:**
```cpp
// Apply preset parameters
for (int i = 0; i < 5; ++i)
{
    // Scale formants by animal size
    auto scaledFreq = currentPreset.formantFreqs[i] * sizeScaler.getFormantMultiplier();
    resonanceSystem.setFormant (i, scaledFreq, currentPreset.formantQs[i]);
}

resonanceSystem.setChestResonance (currentPreset.chestResonance);
resonanceSystem.setThroatResonance (currentPreset.throatResonance);
resonanceSystem.setMix (currentPreset.resonanceMix);

// In processBlock():
auto resonated = resonanceSystem.process (input); // Filters input through formants
```

**What It Does:**
- Creates the vocal tract resonances
- Formants give each animal its unique "voice"
- Chest/throat resonance adds body and depth

### 5. DistortionStage Integration

**File:** `include/dsp/DistortionStage.h`

**Preset Parameters to Apply:**
```cpp
// From PresetParameters
distortionType    // DistortionType enum (SoftClip, Waveshape, etc.)
drive             // Distortion drive amount (0.5 to 5.0)
tone              // Tone control (0.0 to 1.0)
```

**Integration Code:**
```cpp
// Apply preset parameters
distortionStage.setType (static_cast<int> (currentPreset.distortionType));
distortionStage.setDrive (currentPreset.drive);
distortionStage.setTone (currentPreset.tone);

// In processBlock():
auto distorted = distortionStage.process (input); // Adds harmonic richness
```

**What It Does:**
- Adds harmonic richness and complexity
- Simulates vocal cord distortion
- Different types provide different timbres

## Complete DSP Pipeline Integration

### In GrowlPlugin class:

```cpp
class GrowlPlugin : public juce::AudioProcessor
{
private:
    // DSP modules
    Growl::DSP::SizeScaler sizeScaler;
    Growl::DSP::NoiseGenerator noiseGenerator;
    Growl::DSP::OscillatorBank oscillatorBank;
    Growl::DSP::ResonanceSystem resonanceSystem;
    Growl::DSP::DistortionStage distortionStage;

    // Current preset
    PresetParameters currentPreset;

    //==============================================================================
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
        for (int i = 0; i < 5; ++i)
        {
            auto scaledFreq = currentPreset.formantFreqs[i] * sizeScaler.getFormantMultiplier();
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
    void processBlock (juce::AudioBuffer<float>& buffer,
                       juce::MidiBuffer& midiMessages) override
    {
        // DSP Pipeline:
        // 1. Generate noise
        auto noise = noiseGenerator.process();

        // 2. Generate oscillator tone (with size scaling)
        auto oscPitch = midiPitch * sizeScaler.getPitchMultiplier();
        auto osc = oscillatorBank.process (oscPitch);

        // 3. Mix noise + oscillator
        auto mixed = noise * (1.0f - currentPreset.oscillatorMix) +
                     osc * currentPreset.oscillatorMix;

        // 4. Apply formant filtering (vocal tract)
        auto resonated = resonanceSystem.process (mixed);

        // 5. Apply distortion (vocal cord nonlinearity)
        auto distorted = distortionStage.process (resonated);

        // 6. Output to buffer
        buffer.copyFrom (0, 0, distorted, 0, buffer.getNumSamples());
        buffer.copyFrom (1, 0, distorted, 1, buffer.getNumSamples());
    }
};
```

## Preset Loading Integration

### Update GrowlPlugin::loadFactoryPresets():

```cpp
void loadFactoryPresets()
{
    factoryPresets.clear();

    // Load all 50 presets from FactoryPresets::getAllPresets()
    // This requires including "src/FactoryPresets.cpp" or creating a header

    factoryPresets = FactoryPresets::getAllPresets();

    // Set current preset to first one
    if (!factoryPresets.empty())
    {
        currentPreset = factoryPresets[0];
        applyPresetToDSP();
    }
}
```

### Update GrowlPlugin::setCurrentProgram():

```cpp
void setCurrentProgram (int index) override
{
    if (juce::isPositiveAndBelow (index, static_cast<int> (factoryPresets.size())))
    {
        currentPresetIndex = index;
        currentPreset = factoryPresets[index];
        applyPresetToDSP(); // Apply to DSP modules
    }
}
```

## Testing Strategy

### 1. Unit Tests

```cpp
// Test preset loading
TEST (PresetTest, LoadAllPresets)
{
    auto presets = FactoryPresets::getAllPresets();
    EXPECT_EQ (presets.size(), 50);

    // Verify each preset has valid parameters
    for (const auto& preset : presets)
    {
        EXPECT_GT (preset.sizeFeet, 0.0f);
        EXPECT_GE (preset.noiseMix, 0.0f);
        EXPECT_LE (preset.noiseMix, 1.0f);
        // ... more validations
    }
}

// Test DSP integration
TEST (DSPTest, ApplyPreset)
{
    GrowlPlugin plugin;
    plugin.prepareToPlay (48000.0, 512);

    // Load a preset
    plugin.setCurrentProgram (0);

    // Verify DSP modules received correct parameters
    // (Add getter methods to DSP modules if needed)
}
```

### 2. Audio Quality Tests

- **Manual Listening**: Test each preset in standalone app
- **Spectral Analysis**: Verify formant frequencies match presets
- **Dynamic Range**: Check for clipping or distortion artifacts
- **CPU Performance**: Measure CPU usage for each preset

### 3. Performance Benchmarks

```cpp
// CPU usage target: <15% for single voice at 48kHz
BENCHMARK ("Preset CPU Usage")
{
    GrowlPlugin plugin;
    plugin.prepareToPlay (48000.0, 512);

    for (int i = 0; i < plugin.getNumPrograms(); ++i)
    {
        plugin.setCurrentProgram (i);

        // Measure CPU usage
        auto startTime = juce::Time::getHighResolutionTicks();
        plugin.processBlock (buffer, midi);
        auto endTime = juce::Time::getHighResolutionTicks();

        auto cpuPercent = calculateCPUPercent (startTime, endTime);
        EXPECT_LT (cpuPercent, 15.0f);
    }
}
```

## Implementation Checklist

- [ ] Update `GrowlPlugin::loadFactoryPresets()` to call `FactoryPresets::getAllPresets()`
- [ ] Add DSP module member variables to `GrowlPlugin` class
- [ ] Implement `applyPresetToDSP()` method
- [ ] Update `processBlock()` to use complete DSP pipeline
- [ ] Create header file for `FactoryPresets` class (or include .cpp in plugin)
- [ ] Test compilation with updated CMakeLists.txt
- [ ] Verify all 50 presets load without errors
- [ ] Test audio output for representative presets
- [ ] Measure CPU performance
- [ ] Create preset auditioning utility

## Next Steps

1. **Create FactoryPresets.h** header file with class declaration
2. **Integrate DSP modules** into GrowlPlugin class
3. **Implement applyPresetToDSP()** method
4. **Update processBlock()** with complete DSP pipeline
5. **Test compilation** and verify no errors
6. **Audio quality testing** with representative presets
7. **CPU performance validation**

---

**Status**: Preset system complete, DSP integration in progress
**Estimated Completion**: 2-3 hours for full DSP integration
**Testing Required**: Audio quality + CPU performance validation
