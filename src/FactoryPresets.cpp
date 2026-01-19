/*
  ==============================================================================

    FactoryPresets.cpp
    Created: 19 Jan 2026 4:00:00pm
    Author:  White Room Audio

    Factory presets for Growl animal vocal synthesis instrument.
    50 presets: 25 real animals + 25 imaginary creatures.

  ==============================================================================
*/

#include "dsp/Preset.h"
#include <vector>

//==============================================================================
/**
    Factory presets for Growl instrument
*/
class FactoryPresets
{
public:
    //==============================================================================
    static std::vector<PresetParameters> getAllPresets()
    {
        std::vector<PresetParameters> presets;

        //==========================================================================
        // BIG CATS (10 presets)
        //==========================================================================

        // 1. Lion Roar
        PresetParameters lion;
        lion.animalName = "Lion";
        lion.presetName = "Lion Roar";
        lion.sizeFeet = 9.0f;
        lion.noiseType = NoiseType::PinkMixed;
        lion.oscillatorType = OscillatorType::Detuned;
        lion.formantFreqs[0] = 200.0f; lion.formantFreqs[1] = 440.0f; lion.formantFreqs[2] = 800.0f;
        lion.formantFreqs[3] = 1500.0f; lion.formantFreqs[4] = 2500.0f;
        lion.distortionType = DistortionType::SoftClip;
        lion.drive = 2.0f;
        lion.resonanceMix = 0.7f;
        presets.push_back (lion);

        // 2. Tiger Growl
        PresetParameters tiger;
        tiger.animalName = "Tiger";
        tiger.presetName = "Tiger Growl";
        tiger.sizeFeet = 10.0f;
        tiger.noiseType = NoiseType::Pink;
        tiger.oscillatorType = OscillatorType::DPW;
        tiger.formantFreqs[0] = 180.0f; tiger.formantFreqs[1] = 420.0f; tiger.formantFreqs[2] = 780.0f;
        tiger.formantFreqs[3] = 1400.0f; tiger.formantFreqs[4] = 2400.0f;
        tiger.distortionType = DistortionType::Waveshape;
        tiger.drive = 3.0f;
        tiger.resonanceMix = 0.6f;
        presets.push_back (tiger);

        // 3. Leopard Snarl
        PresetParameters leopard;
        leopard.animalName = "Leopard";
        leopard.presetName = "Leopard Snarl";
        leopard.sizeFeet = 7.0f;
        leopard.noiseType = NoiseType::Bandpass;
        leopard.oscillatorType = OscillatorType::PolyBLEP;
        leopard.formantFreqs[0] = 250.0f; leopard.formantFreqs[1] = 500.0f; leopard.formantFreqs[2] = 900.0f;
        leopard.formantFreqs[3] = 1600.0f; leopard.formantFreqs[4] = 2800.0f;
        leopard.distortionType = DistortionType::HarmonicBalancer;
        leopard.drive = 2.5f;
        leopard.resonanceMix = 0.5f;
        presets.push_back (leopard);

        // 4. Jaguar Growl
        PresetParameters jaguar;
        jaguar.animalName = "Jaguar";
        jaguar.presetName = "Jaguar Growl";
        jaguar.sizeFeet = 6.5f;
        jaguar.noiseType = NoiseType::Brown;
        jaguar.oscillatorType = OscillatorType::Wavetable;
        jaguar.formantFreqs[0] = 220.0f; jaguar.formantFreqs[1] = 480.0f; jaguar.formantFreqs[2] = 860.0f;
        jaguar.formantFreqs[3] = 1500.0f; jaguar.formantFreqs[4] = 2600.0f;
        jaguar.distortionType = DistortionType::Chebyshev;
        jaguar.drive = 2.8f;
        jaguar.resonanceMix = 0.65f;
        presets.push_back (jaguar);

        // 5. Cheetah Chirp
        PresetParameters cheetah;
        cheetah.animalName = "Cheetah";
        cheetah.presetName = "Cheetah Chirp";
        cheetah.sizeFeet = 5.0f;
        cheetah.noiseType = NoiseType::White;
        cheetah.oscillatorType = OscillatorType::Detuned;
        cheetah.formantFreqs[0] = 300.0f; cheetah.formantFreqs[1] = 550.0f; cheetah.formantFreqs[2] = 1000.0f;
        cheetah.formantFreqs[3] = 1800.0f; cheetah.formantFreqs[4] = 3000.0f;
        cheetah.distortionType = DistortionType::SoftClip;
        cheetah.drive = 1.5f;
        cheetah.resonanceMix = 0.8f;
        presets.push_back (cheetah);

        // 6. Snow Leopard
        PresetParameters snowLeopard;
        snowLeopard.animalName = "Snow Leopard";
        snowLeopard.presetName = "Snow Leopard";
        snowLeopard.sizeFeet = 7.5f;
        snowLeopard.noiseType = NoiseType::Pink;
        snowLeopard.oscillatorType = OscillatorType::PolyBLEP;
        snowLeopard.formantFreqs[0] = 200.0f; snowLeopard.formantFreqs[1] = 450.0f; snowLeopard.formantFreqs[2] = 850.0f;
        snowLeopard.formantFreqs[3] = 1500.0f; snowLeopard.formantFreqs[4] = 2500.0f;
        snowLeopard.distortionType = DistortionType::Wavefolder;
        snowLeopard.drive = 2.2f;
        snowLeopard.resonanceMix = 0.6f;
        presets.push_back (snowLeopard);

        // 7. Cougar Scream
        PresetParameters cougar;
        cougar.animalName = "Cougar";
        cougar.presetName = "Cougar Scream";
        cougar.sizeFeet = 8.0f;
        cougar.noiseType = NoiseType::Bandpass;
        cougar.oscillatorType = OscillatorType::DPW;
        cougar.formantFreqs[0] = 280.0f; cougar.formantFreqs[1] = 520.0f; cougar.formantFreqs[2] = 920.0f;
        cougar.formantFreqs[3] = 1600.0f; cougar.formantFreqs[4] = 2700.0f;
        cougar.distortionType = DistortionType::Bitcrush;
        cougar.drive = 2.0f;
        cougar.resonanceMix = 0.7f;
        presets.push_back (cougar);

        // 8. Liger Roar
        PresetParameters liger;
        liger.animalName = "Liger";
        liger.presetName = "Liger Roar";
        liger.sizeFeet = 12.0f;
        liger.noiseType = NoiseType::PinkMixed;
        liger.oscillatorType = OscillatorType::Detuned;
        liger.formantFreqs[0] = 150.0f; liger.formantFreqs[1] = 350.0f; liger.formantFreqs[2] = 650.0f;
        liger.formantFreqs[3] = 1200.0f; liger.formantFreqs[4] = 2000.0f;
        liger.distortionType = DistortionType::SoftClip;
        liger.drive = 3.5f;
        liger.resonanceMix = 0.75f;
        presets.push_back (liger);

        // 9. Bobcat Growl
        PresetParameters bobcat;
        bobcat.animalName = "Bobcat";
        bobcat.presetName = "Bobcat Growl";
        bobcat.sizeFeet = 4.0f;
        bobcat.noiseType = NoiseType::Pink;
        bobcat.oscillatorType = OscillatorType::Wavetable;
        bobcat.formantFreqs[0] = 350.0f; bobcat.formantFreqs[1] = 650.0f; bobcat.formantFreqs[2] = 1100.0f;
        bobcat.formantFreqs[3] = 1900.0f; bobcat.formantFreqs[4] = 3200.0f;
        bobcat.distortionType = DistortionType::Waveshape;
        bobcat.drive = 1.8f;
        bobcat.resonanceMix = 0.55f;
        presets.push_back (bobcat);

        // 10. Panther Purr
        PresetParameters panther;
        panther.animalName = "Panther";
        panther.presetName = "Panther Purr";
        panther.sizeFeet = 8.5f;
        panther.noiseType = NoiseType::Brown;
        panther.oscillatorType = OscillatorType::PolyBLEP;
        panther.formantFreqs[0] = 180.0f; panther.formantFreqs[1] = 400.0f; panther.formantFreqs[2] = 750.0f;
        panther.formantFreqs[3] = 1300.0f; panther.formantFreqs[4] = 2300.0f;
        panther.distortionType = DistortionType::SoftClip;
        panther.drive = 1.2f;
        panther.resonanceMix = 0.9f;
        presets.push_back (panther);

        //==========================================================================
        // CANINES (10 presets)
        //==========================================================================

        // 11. Wolf Howl
        PresetParameters wolf;
        wolf.animalName = "Wolf";
        wolf.presetName = "Wolf Howl";
        wolf.sizeFeet = 6.0f;
        wolf.noiseType = NoiseType::Pink;
        wolf.oscillatorType = OscillatorType::DPW;
        wolf.formantFreqs[0] = 250.0f; wolf.formantFreqs[1] = 500.0f; wolf.formantFreqs[2] = 900.0f;
        wolf.formantFreqs[3] = 1600.0f; wolf.formantFreqs[4] = 2800.0f;
        wolf.distortionType = DistortionType::SoftClip;
        wolf.drive = 1.5f;
        wolf.resonanceMix = 0.6f;
        presets.push_back (wolf);

        // 12. Dire Wolf
        PresetParameters direWolf;
        direWolf.animalName = "Dire Wolf";
        direWolf.presetName = "Dire Wolf";
        direWolf.sizeFeet = 7.0f;
        direWolf.noiseType = NoiseType::PinkMixed;
        direWolf.oscillatorType = OscillatorType::Detuned;
        direWolf.formantFreqs[0] = 200.0f; direWolf.formantFreqs[1] = 420.0f; direWolf.formantFreqs[2] = 800.0f;
        direWolf.formantFreqs[3] = 1400.0f; direWolf.formantFreqs[4] = 2400.0f;
        direWolf.distortionType = DistortionType::Waveshape;
        direWolf.drive = 2.5f;
        direWolf.resonanceMix = 0.7f;
        presets.push_back (direWolf);

        // 13. Fox Bark
        PresetParameters fox;
        fox.animalName = "Fox";
        fox.presetName = "Fox Bark";
        fox.sizeFeet = 3.5f;
        fox.noiseType = NoiseType::Bandpass;
        fox.oscillatorType = OscillatorType::PolyBLEP;
        fox.formantFreqs[0] = 400.0f; fox.formantFreqs[1] = 700.0f; fox.formantFreqs[2] = 1200.0f;
        fox.formantFreqs[3] = 2000.0f; fox.formantFreqs[4] = 3500.0f;
        fox.distortionType = DistortionType::SoftClip;
        fox.drive = 1.0f;
        fox.resonanceMix = 0.5f;
        presets.push_back (fox);

        // 14. Coyote Howl
        PresetParameters coyote;
        coyote.animalName = "Coyote";
        coyote.presetName = "Coyote Howl";
        coyote.sizeFeet = 4.5f;
        coyote.noiseType = NoiseType::White;
        coyote.oscillatorType = OscillatorType::Wavetable;
        coyote.formantFreqs[0] = 350.0f; coyote.formantFreqs[1] = 650.0f; coyote.formantFreqs[2] = 1100.0f;
        coyote.formantFreqs[3] = 1900.0f; coyote.formantFreqs[4] = 3200.0f;
        coyote.distortionType = DistortionType::HarmonicBalancer;
        coyote.drive = 1.3f;
        coyote.resonanceMix = 0.55f;
        presets.push_back (coyote);

        // 15. Dingo Growl
        PresetParameters dingo;
        dingo.animalName = "Dingo";
        dingo.presetName = "Dingo Growl";
        dingo.sizeFeet = 5.0f;
        dingo.noiseType = NoiseType::Pink;
        dingo.oscillatorType = OscillatorType::DPW;
        dingo.formantFreqs[0] = 300.0f; dingo.formantFreqs[1] = 580.0f; dingo.formantFreqs[2] = 1000.0f;
        dingo.formantFreqs[3] = 1800.0f; dingo.formantFreqs[4] = 3000.0f;
        dingo.distortionType = DistortionType::SoftClip;
        dingo.drive = 1.6f;
        dingo.resonanceMix = 0.6f;
        presets.push_back (dingo);

        // 16. African Wild Dog
        PresetParameters wildDog;
        wildDog.animalName = "African Wild Dog";
        wildDog.presetName = "African Wild Dog";
        wildDog.sizeFeet = 5.5f;
        wildDog.noiseType = NoiseType::Bandpass;
        wildDog.oscillatorType = OscillatorType::Detuned;
        wildDog.formantFreqs[0] = 320.0f; wildDog.formantFreqs[1] = 600.0f; wildDog.formantFreqs[2] = 1050.0f;
        wildDog.formantFreqs[3] = 1850.0f; wildDog.formantFreqs[4] = 3100.0f;
        wildDog.distortionType = DistortionType::Waveshape;
        wildDog.drive = 1.7f;
        wildDog.resonanceMix = 0.58f;
        presets.push_back (wildDog);

        // 17. Hyena Laugh
        PresetParameters hyena;
        hyena.animalName = "Hyena";
        hyena.presetName = "Hyena Laugh";
        hyena.sizeFeet = 6.5f;
        hyena.noiseType = NoiseType::PinkMixed;
        hyena.oscillatorType = OscillatorType::PolyBLEP;
        hyena.formantFreqs[0] = 280.0f; hyena.formantFreqs[1] = 520.0f; hyena.formantFreqs[2] = 920.0f;
        hyena.formantFreqs[3] = 1600.0f; hyena.formantFreqs[4] = 2700.0f;
        hyena.distortionType = DistortionType::Chebyshev;
        hyena.drive = 2.0f;
        hyena.resonanceMix = 0.65f;
        presets.push_back (hyena);

        // 18. Werewolf Growl
        PresetParameters werewolf;
        werewolf.animalName = "Werewolf";
        werewolf.presetName = "Werewolf Growl";
        werewolf.sizeFeet = 8.0f;
        werewolf.noiseType = NoiseType::Brown;
        werewolf.oscillatorType = OscillatorType::Detuned;
        werewolf.formantFreqs[0] = 150.0f; werewolf.formantFreqs[1] = 350.0f; werewolf.formantFreqs[2] = 650.0f;
        werewolf.formantFreqs[3] = 1200.0f; werewolf.formantFreqs[4] = 2000.0f;
        werewolf.distortionType = DistortionType::Wavefolder;
        werewolf.drive = 4.0f;
        werewolf.resonanceMix = 0.8f;
        presets.push_back (werewolf);

        // 19. Dog Bark
        PresetParameters dog;
        dog.animalName = "Domestic Dog";
        dog.presetName = "Dog Bark";
        dog.sizeFeet = 2.5f;
        dog.noiseType = NoiseType::White;
        dog.oscillatorType = OscillatorType::Wavetable;
        dog.formantFreqs[0] = 450.0f; dog.formantFreqs[1] = 800.0f; dog.formantFreqs[2] = 1400.0f;
        dog.formantFreqs[3] = 2400.0f; dog.formantFreqs[4] = 4000.0f;
        dog.distortionType = DistortionType::SoftClip;
        dog.drive = 0.8f;
        dog.resonanceMix = 0.5f;
        presets.push_back (dog);

        // 20. Gray Wolf
        PresetParameters grayWolf;
        grayWolf.animalName = "Gray Wolf";
        grayWolf.presetName = "Gray Wolf";
        grayWolf.sizeFeet = 6.2f;
        grayWolf.noiseType = NoiseType::Pink;
        grayWolf.oscillatorType = OscillatorType::DPW;
        grayWolf.formantFreqs[0] = 240.0f; grayWolf.formantFreqs[1] = 480.0f; grayWolf.formantFreqs[2] = 880.0f;
        grayWolf.formantFreqs[3] = 1550.0f; grayWolf.formantFreqs[4] = 2650.0f;
        grayWolf.distortionType = DistortionType::SoftClip;
        grayWolf.drive = 1.7f;
        grayWolf.resonanceMix = 0.62f;
        presets.push_back (grayWolf);

        //==========================================================================
        // BEARS (10 presets)
        //==========================================================================

        // 21. Grizzly Growl
        PresetParameters grizzly;
        grizzly.animalName = "Grizzly Bear";
        grizzly.presetName = "Grizzly Growl";
        grizzly.sizeFeet = 10.0f;
        grizzly.noiseType = NoiseType::Brown;
        grizzly.oscillatorType = OscillatorType::Detuned;
        grizzly.formantFreqs[0] = 120.0f; grizzly.formantFreqs[1] = 280.0f; grizzly.formantFreqs[2] = 520.0f;
        grizzly.formantFreqs[3] = 950.0f; grizzly.formantFreqs[4] = 1600.0f;
        grizzly.distortionType = DistortionType::Waveshape;
        grizzly.drive = 3.0f;
        grizzly.resonanceMix = 0.8f;
        presets.push_back (grizzly);

        // 22. Polar Bear Roar
        PresetParameters polarBear;
        polarBear.animalName = "Polar Bear";
        polarBear.presetName = "Polar Bear Roar";
        polarBear.sizeFeet = 10.5f;
        polarBear.noiseType = NoiseType::Pink;
        polarBear.oscillatorType = OscillatorType::DPW;
        polarBear.formantFreqs[0] = 110.0f; polarBear.formantFreqs[1] = 260.0f; polarBear.formantFreqs[2] = 500.0f;
        polarBear.formantFreqs[3] = 900.0f; polarBear.formantFreqs[4] = 1550.0f;
        polarBear.distortionType = DistortionType::SoftClip;
        polarBear.drive = 2.8f;
        polarBear.resonanceMix = 0.75f;
        presets.push_back (polarBear);

        // 23. Kodiak Bear
        PresetParameters kodiak;
        kodiak.animalName = "Kodiak Bear";
        kodiak.presetName = "Kodiak Bear";
        kodiak.sizeFeet = 11.0f;
        kodiak.noiseType = NoiseType::Brown;
        kodiak.oscillatorType = OscillatorType::Detuned;
        kodiak.formantFreqs[0] = 100.0f; kodiak.formantFreqs[1] = 250.0f; kodiak.formantFreqs[2] = 480.0f;
        kodiak.formantFreqs[3] = 880.0f; kodiak.formantFreqs[4] = 1500.0f;
        kodiak.distortionType = DistortionType::Wavefolder;
        kodiak.drive = 3.5f;
        kodiak.resonanceMix = 0.85f;
        presets.push_back (kodiak);

        // 24. Black Bear
        PresetParameters blackBear;
        blackBear.animalName = "Black Bear";
        blackBear.presetName = "Black Bear";
        blackBear.sizeFeet = 7.0f;
        blackBear.noiseType = NoiseType::Pink;
        blackBear.oscillatorType = OscillatorType::PolyBLEP;
        blackBear.formantFreqs[0] = 150.0f; blackBear.formantFreqs[1] = 320.0f; blackBear.formantFreqs[2] = 600.0f;
        blackBear.formantFreqs[3] = 1100.0f; blackBear.formantFreqs[4] = 1900.0f;
        blackBear.distortionType = DistortionType::SoftClip;
        blackBear.drive = 2.2f;
        blackBear.resonanceMix = 0.65f;
        presets.push_back (blackBear);

        // 25. Panda Bear
        PresetParameters panda;
        panda.animalName = "Panda Bear";
        panda.presetName = "Panda Bear";
        panda.sizeFeet = 6.0f;
        panda.noiseType = NoiseType::Bandpass;
        panda.oscillatorType = OscillatorType::Wavetable;
        panda.formantFreqs[0] = 180.0f; panda.formantFreqs[1] = 350.0f; panda.formantFreqs[2] = 650.0f;
        panda.formantFreqs[3] = 1200.0f; panda.formantFreqs[4] = 2000.0f;
        panda.distortionType = DistortionType::HarmonicBalancer;
        panda.drive = 1.5f;
        panda.resonanceMix = 0.6f;
        presets.push_back (panda);

        // 26. Sun Bear
        PresetParameters sunBear;
        sunBear.animalName = "Sun Bear";
        sunBear.presetName = "Sun Bear";
        sunBear.sizeFeet = 5.0f;
        sunBear.noiseType = NoiseType::Pink;
        sunBear.oscillatorType = OscillatorType::DPW;
        sunBear.formantFreqs[0] = 200.0f; sunBear.formantFreqs[1] = 400.0f; sunBear.formantFreqs[2] = 750.0f;
        sunBear.formantFreqs[3] = 1350.0f; sunBear.formantFreqs[4] = 2300.0f;
        sunBear.distortionType = DistortionType::SoftClip;
        sunBear.drive = 1.8f;
        sunBear.resonanceMix = 0.58f;
        presets.push_back (sunBear);

        // 27. Spectacled Bear
        PresetParameters spectacledBear;
        spectacledBear.animalName = "Spectacled Bear";
        spectacledBear.presetName = "Spectacled Bear";
        spectacledBear.sizeFeet = 6.5f;
        spectacledBear.noiseType = NoiseType::Brown;
        spectacledBear.oscillatorType = OscillatorType::PolyBLEP;
        spectacledBear.formantFreqs[0] = 170.0f; spectacledBear.formantFreqs[1] = 340.0f; spectacledBear.formantFreqs[2] = 620.0f;
        spectacledBear.formantFreqs[3] = 1150.0f; spectacledBear.formantFreqs[4] = 1950.0f;
        spectacledBear.distortionType = DistortionType::Waveshape;
        spectacledBear.drive = 2.0f;
        spectacledBear.resonanceMix = 0.62f;
        presets.push_back (spectacledBear);

        // 28. Cave Bear
        PresetParameters caveBear;
        caveBear.animalName = "Cave Bear";
        caveBear.presetName = "Cave Bear";
        caveBear.sizeFeet = 11.5f;
        caveBear.noiseType = NoiseType::PinkMixed;
        caveBear.oscillatorType = OscillatorType::Detuned;
        caveBear.formantFreqs[0] = 90.0f; caveBear.formantFreqs[1] = 220.0f; caveBear.formantFreqs[2] = 420.0f;
        caveBear.formantFreqs[3] = 780.0f; caveBear.formantFreqs[4] = 1300.0f;
        caveBear.distortionType = DistortionType::Chebyshev;
        caveBear.drive = 4.0f;
        caveBear.resonanceMix = 0.9f;
        presets.push_back (caveBear);

        // 29. Teddy Bear
        PresetParameters teddyBear;
        teddyBear.animalName = "Teddy Bear";
        teddyBear.presetName = "Teddy Bear";
        teddyBear.sizeFeet = 1.0f;
        teddyBear.noiseType = NoiseType::White;
        teddyBear.oscillatorType = OscillatorType::Wavetable;
        teddyBear.formantFreqs[0] = 500.0f; teddyBear.formantFreqs[1] = 900.0f; teddyBear.formantFreqs[2] = 1600.0f;
        teddyBear.formantFreqs[3] = 2800.0f; teddyBear.formantFreqs[4] = 4800.0f;
        teddyBear.distortionType = DistortionType::SoftClip;
        teddyBear.drive = 0.5f;
        teddyBear.resonanceMix = 0.4f;
        presets.push_back (teddyBear);

        // 30. Brown Bear
        PresetParameters brownBear;
        brownBear.animalName = "Brown Bear";
        brownBear.presetName = "Brown Bear";
        brownBear.sizeFeet = 9.5f;
        brownBear.noiseType = NoiseType::Brown;
        brownBear.oscillatorType = OscillatorType::DPW;
        brownBear.formantFreqs[0] = 115.0f; brownBear.formantFreqs[1] = 270.0f; brownBear.formantFreqs[2] = 500.0f;
        brownBear.formantFreqs[3] = 920.0f; brownBear.formantFreqs[4] = 1570.0f;
        brownBear.distortionType = DistortionType::Waveshape;
        brownBear.drive = 2.9f;
        brownBear.resonanceMix = 0.78f;
        presets.push_back (brownBear);

        //==========================================================================
        // MYTHICAL (10 presets)
        //==========================================================================

        // 31. Dragon Roar
        PresetParameters dragon;
        dragon.animalName = "Dragon";
        dragon.presetName = "Dragon Roar";
        dragon.sizeFeet = 50.0f;
        dragon.noiseType = NoiseType::PinkMixed;
        dragon.oscillatorType = OscillatorType::Detuned;
        dragon.formantFreqs[0] = 50.0f; dragon.formantFreqs[1] = 120.0f; dragon.formantFreqs[2] = 220.0f;
        dragon.formantFreqs[3] = 400.0f; dragon.formantFreqs[4] = 700.0f;
        dragon.distortionType = DistortionType::Wavefolder;
        dragon.drive = 5.0f;
        dragon.resonanceMix = 0.95f;
        presets.push_back (dragon);

        // 32. Werewolf Howl (Duplicate from canines, using different parameters)
        PresetParameters werewolfHowl;
        werewolfHowl.animalName = "Werewolf";
        werewolfHowl.presetName = "Werewolf Howl";
        werewolfHowl.sizeFeet = 8.0f;
        werewolfHowl.noiseType = NoiseType::Brown;
        werewolfHowl.oscillatorType = OscillatorType::PolyBLEP;
        werewolfHowl.formantFreqs[0] = 140.0f; werewolfHowl.formantFreqs[1] = 320.0f; werewolfHowl.formantFreqs[2] = 600.0f;
        werewolfHowl.formantFreqs[3] = 1100.0f; werewolfHowl.formantFreqs[4] = 1900.0f;
        werewolfHowl.distortionType = DistortionType::Bitcrush;
        werewolfHowl.drive = 3.5f;
        werewolfHowl.resonanceMix = 0.75f;
        presets.push_back (werewolfHowl);

        // 33. Kraken Scream
        PresetParameters kraken;
        kraken.animalName = "Kraken";
        kraken.presetName = "Kraken Scream";
        kraken.sizeFeet = 100.0f;
        kraken.noiseType = NoiseType::Bandpass;
        kraken.oscillatorType = OscillatorType::Detuned;
        kraken.formantFreqs[0] = 30.0f; kraken.formantFreqs[1] = 70.0f; kraken.formantFreqs[2] = 130.0f;
        kraken.formantFreqs[3] = 240.0f; kraken.formantFreqs[4] = 420.0f;
        kraken.distortionType = DistortionType::Chebyshev;
        kraken.drive = 4.5f;
        kraken.resonanceMix = 0.85f;
        presets.push_back (kraken);

        // 34. Phoenix Cry
        PresetParameters phoenix;
        phoenix.animalName = "Phoenix";
        phoenix.presetName = "Phoenix Cry";
        phoenix.sizeFeet = 8.0f;
        phoenix.noiseType = NoiseType::Pink;
        phoenix.oscillatorType = OscillatorType::Wavetable;
        phoenix.formantFreqs[0] = 400.0f; phoenix.formantFreqs[1] = 750.0f; phoenix.formantFreqs[2] = 1400.0f;
        phoenix.formantFreqs[3] = 2400.0f; phoenix.formantFreqs[4] = 4200.0f;
        phoenix.distortionType = DistortionType::HarmonicBalancer;
        phoenix.drive = 2.0f;
        phoenix.resonanceMix = 0.6f;
        presets.push_back (phoenix);

        // 35. Griffin Screech
        PresetParameters griffin;
        griffin.animalName = "Griffin";
        griffin.presetName = "Griffin Screech";
        griffin.sizeFeet = 10.0f;
        griffin.noiseType = NoiseType::White;
        griffin.oscillatorType = OscillatorType::DPW;
        griffin.formantFreqs[0] = 350.0f; griffin.formantFreqs[1] = 700.0f; griffin.formantFreqs[2] = 1250.0f;
        griffin.formantFreqs[3] = 2200.0f; griffin.formantFreqs[4] = 3800.0f;
        griffin.distortionType = DistortionType::SoftClip;
        griffin.drive = 2.5f;
        griffin.resonanceMix = 0.65f;
        presets.push_back (griffin);

        // 36. Chimera Roar
        PresetParameters chimera;
        chimera.animalName = "Chimera";
        chimera.presetName = "Chimera Roar";
        chimera.sizeFeet = 12.0f;
        chimera.noiseType = NoiseType::PinkMixed;
        chimera.oscillatorType = OscillatorType::Detuned;
        chimera.formantFreqs[0] = 100.0f; chimera.formantFreqs[1] = 240.0f; chimera.formantFreqs[2] = 450.0f;
        chimera.formantFreqs[3] = 820.0f; chimera.formantFreqs[4] = 1400.0f;
        chimera.distortionType = DistortionType::Waveshape;
        chimera.drive = 4.0f;
        chimera.resonanceMix = 0.8f;
        presets.push_back (chimera);

        // 37. Yeti Growl
        PresetParameters yeti;
        yeti.animalName = "Yeti";
        yeti.presetName = "Yeti Growl";
        yeti.sizeFeet = 9.0f;
        yeti.noiseType = NoiseType::Brown;
        yeti.oscillatorType = OscillatorType::PolyBLEP;
        yeti.formantFreqs[0] = 130.0f; yeti.formantFreqs[1] = 300.0f; yeti.formantFreqs[2] = 550.0f;
        yeti.formantFreqs[3] = 1000.0f; yeti.formantFreqs[4] = 1700.0f;
        yeti.distortionType = DistortionType::Wavefolder;
        yeti.drive = 3.2f;
        yeti.resonanceMix = 0.72f;
        presets.push_back (yeti);

        // 38. Basilisk Hiss
        PresetParameters basilisk;
        basilisk.animalName = "Basilisk";
        basilisk.presetName = "Basilisk Hiss";
        basilisk.sizeFeet = 15.0f;
        basilisk.noiseType = NoiseType::Bandpass;
        basilisk.oscillatorType = OscillatorType::Wavetable;
        basilisk.formantFreqs[0] = 80.0f; basilisk.formantFreqs[1] = 180.0f; basilisk.formantFreqs[2] = 340.0f;
        basilisk.formantFreqs[3] = 620.0f; basilisk.formantFreqs[4] = 1100.0f;
        basilisk.distortionType = DistortionType::SoftClip;
        basilisk.drive = 2.8f;
        basilisk.resonanceMix = 0.7f;
        presets.push_back (basilisk);

        // 39. Cerberus Bark
        PresetParameters cerberus;
        cerberus.animalName = "Cerberus";
        cerberus.presetName = "Cerberus Bark";
        cerberus.sizeFeet = 25.0f;
        cerberus.noiseType = NoiseType::PinkMixed;
        cerberus.oscillatorType = OscillatorType::Detuned;
        cerberus.formantFreqs[0] = 60.0f; cerberus.formantFreqs[1] = 140.0f; cerberus.formantFreqs[2] = 260.0f;
        cerberus.formantFreqs[3] = 480.0f; cerberus.formantFreqs[4] = 820.0f;
        cerberus.distortionType = DistortionType::Chebyshev;
        cerberus.drive = 4.8f;
        cerberus.resonanceMix = 0.9f;
        presets.push_back (cerberus);

        // 40. Hydra Roar
        PresetParameters hydra;
        hydra.animalName = "Hydra";
        hydra.presetName = "Hydra Roar";
        hydra.sizeFeet = 30.0f;
        hydra.noiseType = NoiseType::Brown;
        hydra.oscillatorType = OscillatorType::Detuned;
        hydra.formantFreqs[0] = 50.0f; hydra.formantFreqs[1] = 110.0f; hydra.formantFreqs[2] = 210.0f;
        hydra.formantFreqs[3] = 380.0f; hydra.formantFreqs[4] = 660.0f;
        hydra.distortionType = DistortionType::Wavefolder;
        hydra.drive = 5.0f;
        hydra.resonanceMix = 0.95f;
        presets.push_back (hydra);

        //==========================================================================
        // SCIFI (10 presets)
        //==========================================================================

        // 41. Alien Growl
        PresetParameters alien;
        alien.animalName = "Alien Creature";
        alien.presetName = "Alien Growl";
        alien.sizeFeet = 7.0f;
        alien.noiseType = NoiseType::Bandpass;
        alien.oscillatorType = OscillatorType::Wavetable;
        alien.formantFreqs[0] = 300.0f; alien.formantFreqs[1] = 700.0f; alien.formantFreqs[2] = 1300.0f;
        alien.formantFreqs[3] = 2400.0f; alien.formantFreqs[4] = 4200.0f;
        alien.distortionType = DistortionType::Bitcrush;
        alien.drive = 2.5f;
        alien.resonanceMix = 0.6f;
        presets.push_back (alien);

        // 42. Robot Voice
        PresetParameters robot;
        robot.animalName = "Robot";
        robot.presetName = "Robot Voice";
        robot.sizeFeet = 6.5f;
        robot.noiseType = NoiseType::White;
        robot.oscillatorType = OscillatorType::PolyBLEP;
        robot.formantFreqs[0] = 250.0f; robot.formantFreqs[1] = 550.0f; robot.formantFreqs[2] = 1000.0f;
        robot.formantFreqs[3] = 1800.0f; robot.formantFreqs[4] = 3200.0f;
        robot.distortionType = DistortionType::SoftClip;
        robot.drive = 1.5f;
        robot.resonanceMix = 0.5f;
        presets.push_back (robot);

        // 43. Cyber Wolf
        PresetParameters cyberWolf;
        cyberWolf.animalName = "Cybernetic Wolf";
        cyberWolf.presetName = "Cyber Wolf";
        cyberWolf.sizeFeet = 7.5f;
        cyberWolf.noiseType = NoiseType::PinkMixed;
        cyberWolf.oscillatorType = OscillatorType::Detuned;
        cyberWolf.formantFreqs[0] = 200.0f; cyberWolf.formantFreqs[1] = 420.0f; cyberWolf.formantFreqs[2] = 780.0f;
        cyberWolf.formantFreqs[3] = 1400.0f; cyberWolf.formantFreqs[4] = 2400.0f;
        cyberWolf.distortionType = DistortionType::Chebyshev;
        cyberWolf.drive = 3.0f;
        cyberWolf.resonanceMix = 0.7f;
        presets.push_back (cyberWolf);

        // 44. Mutant Beast
        PresetParameters mutant;
        mutant.animalName = "Mutant";
        mutant.presetName = "Mutant Beast";
        mutant.sizeFeet = 8.0f;
        mutant.noiseType = NoiseType::Brown;
        mutant.oscillatorType = OscillatorType::Wavefolder;
        mutant.formantFreqs[0] = 150.0f; mutant.formantFreqs[1] = 320.0f; mutant.formantFreqs[2] = 580.0f;
        mutant.formantFreqs[3] = 1050.0f; mutant.formantFreqs[4] = 1800.0f;
        mutant.distortionType = DistortionType::Wavefolder;
        mutant.drive = 4.0f;
        mutant.resonanceMix = 0.75f;
        presets.push_back (mutant);

        // 45. Space Monster
        PresetParameters spaceMonster;
        spaceMonster.animalName = "Space Creature";
        spaceMonster.presetName = "Space Monster";
        spaceMonster.sizeFeet = 100.0f;
        spaceMonster.noiseType = NoiseType::Bandpass;
        spaceMonster.oscillatorType = OscillatorType::Detuned;
        spaceMonster.formantFreqs[0] = 40.0f; spaceMonster.formantFreqs[1] = 90.0f; spaceMonster.formantFreqs[2] = 170.0f;
        spaceMonster.formantFreqs[3] = 310.0f; spaceMonster.formantFreqs[4] = 540.0f;
        spaceMonster.distortionType = DistortionType::Waveshape;
        spaceMonster.drive = 5.0f;
        spaceMonster.resonanceMix = 0.95f;
        presets.push_back (spaceMonster);

        // 46. AI Voice
        PresetParameters aiVoice;
        aiVoice.animalName = "Artificial Intelligence";
        aiVoice.presetName = "AI Voice";
        aiVoice.sizeFeet = 0.0f;
        aiVoice.noiseType = NoiseType::White;
        aiVoice.oscillatorType = OscillatorType::Wavetable;
        aiVoice.formantFreqs[0] = 350.0f; aiVoice.formantFreqs[1] = 750.0f; aiVoice.formantFreqs[2] = 1400.0f;
        aiVoice.formantFreqs[3] = 2500.0f; aiVoice.formantFreqs[4] = 4400.0f;
        aiVoice.distortionType = DistortionType::SoftClip;
        aiVoice.drive = 0.8f;
        aiVoice.resonanceMix = 0.5f;
        presets.push_back (aiVoice);

        // 47. Genetic Experiment
        PresetParameters genetic;
        genetic.animalName = "Hybrid";
        genetic.presetName = "Genetic Experiment";
        genetic.sizeFeet = 9.0f;
        genetic.noiseType = NoiseType::PinkMixed;
        genetic.oscillatorType = OscillatorType::Detuned;
        genetic.formantFreqs[0] = 120.0f; genetic.formantFreqs[1] = 280.0f; genetic.formantFreqs[2] = 520.0f;
        genetic.formantFreqs[3] = 950.0f; genetic.formantFreqs[4] = 1650.0f;
        genetic.distortionType = DistortionType::HarmonicBalancer;
        genetic.drive = 3.5f;
        genetic.resonanceMix = 0.78f;
        presets.push_back (genetic);

        // 48. Cybernetic Tiger
        PresetParameters cyberTiger;
        cyberTiger.animalName = "Cyber-Tiger";
        cyberTiger.presetName = "Cybernetic Tiger";
        cyberTiger.sizeFeet = 11.0f;
        cyberTiger.noiseType = NoiseType::Brown;
        cyberTiger.oscillatorType = OscillatorType::DPW;
        cyberTiger.formantFreqs[0] = 100.0f; cyberTiger.formantFreqs[1] = 230.0f; cyberTiger.formantFreqs[2] = 430.0f;
        cyberTiger.formantFreqs[3] = 780.0f; cyberTiger.formantFreqs[4] = 1350.0f;
        cyberTiger.distortionType = DistortionType::Chebyshev;
        cyberTiger.drive = 4.2f;
        cyberTiger.resonanceMix = 0.82f;
        presets.push_back (cyberTiger);

        // 49. Plasma Creature
        PresetParameters plasma;
        plasma.animalName = "Energy Being";
        plasma.presetName = "Plasma Creature";
        plasma.sizeFeet = 15.0f;
        plasma.noiseType = NoiseType::Bandpass;
        plasma.oscillatorType = OscillatorType::Wavetable;
        plasma.formantFreqs[0] = 200.0f; plasma.formantFreqs[1] = 500.0f; plasma.formantFreqs[2] = 900.0f;
        plasma.formantFreqs[3] = 1600.0f; plasma.formantFreqs[4] = 2800.0f;
        plasma.distortionType = DistortionType::Wavefolder;
        plasma.drive = 4.5f;
        plasma.resonanceMix = 0.7f;
        presets.push_back (plasma);

        // 50. Quantum Beast
        PresetParameters quantum;
        quantum.animalName = "Quantum Entity";
        quantum.presetName = "Quantum Beast";
        quantum.sizeFeet = 0.0f; // Variable
        quantum.noiseType = NoiseType::PinkMixed;
        quantum.oscillatorType = OscillatorType::Detuned;
        quantum.formantFreqs[0] = 150.0f; quantum.formantFreqs[1] = 350.0f; quantum.formantFreqs[2] = 650.0f;
        quantum.formantFreqs[3] = 1200.0f; quantum.formantFreqs[4] = 2100.0f;
        quantum.distortionType = DistortionType::Chebyshev;
        quantum.drive = 5.0f;
        quantum.resonanceMix = 0.9f;
        presets.push_back (quantum);

        return presets;
    }
};
