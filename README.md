# Growl 🦁

Animal Vocal Synthesis Instrument for JUCE

## Overview

Growl is a next-generation animal vocal synthesis instrument that creates realistic growl, roar, and vocal textures using advanced DSP techniques including:

- **6 Noise Types**: White, Pink, Brown, Bandpass, Pink Mixed, Custom Mix
- **Formant Resonance**: 5 parallel formant filters for vocal tract modeling
- **Size Scaling**: Physical modeling of animal size affecting pitch and timbre
- **Distortion Stage**: 7 distortion types for aggressive vocal textures
- **Modulation System**: 4 LFOs + ADSR envelope for parameter modulation
- **16-Voice Polyphony**: Full polyphonic synthesis engine

## Architecture

Growl follows the White Room Plugin Architecture Contract:
- Separate git repository: `https://github.com/bretbouchard/growl`
- All 7 plugin formats: VST3, AU, CLAP, LV2, AUv3, Standalone, DSP
- Pure DSP implementation in `include/dsp/`
- Plugin wrapper in `src/GrowlPlugin.cpp`
- Factory presets in `presets/`

## Building

### Requirements
- JUCE 7.0.0 or later
- CMake 3.15 or later
- Xcode 14 (macOS) / Visual Studio 2022 (Windows)

### Build Instructions

```bash
# Clone repository
git clone https://github.com/bretbouchard/growl.git
cd growl

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build all formats
cmake --build . --config Release

# Install to plugins directory
cmake --install .
```

### Plugin Formats

All 7 formats are built:
- **VST3**: `plugins/vst/growl.vst3`
- **AU**: `plugins/au/growl.component`
- **CLAP**: `plugins/clap/growl.clap`
- **LV2**: `plugins/lv2/growl.lv2`
- **AUv3**: `plugins/auv3/growl.appex`
- **Standalone**: `plugins/standalone/growl.app`
- **DSP**: `plugins/dsp/` (pure DSP, no wrapper)

## Presets

Growl includes 50 factory presets covering:
- **Big Cats** (Lion, Tiger, Leopard, Jaguar)
- **Canines** (Wolf, Dog, Fox, Coyote)
- **Bears** (Grizzly, Polar, Black, Kodiak)
- **Mythical** (Dragon, Werewolf, Monster)
- **Sci-Fi** (Alien, Robot, Creature)
- **Textural** (Atmospheric, Drone, Ambient)

## License

MIT License - See LICENSE file for details

## Author

Bret Bouchard
White Room Audio
https://whiteroomaudio.com

## Version

Version 1.0.0 - January 18, 2026
