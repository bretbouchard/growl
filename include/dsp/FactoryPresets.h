/*
  ==============================================================================

    FactoryPresets.h
    Created: 19 Jan 2026 4:30:00pm
    Author:  White Room Audio

    Factory presets for Growl animal vocal synthesis instrument.

  ==============================================================================
*/

#pragma once

#include "Preset.h"
#include <vector>

//==============================================================================
/**
    Factory presets for Growl instrument

    This class provides all 50 factory presets (25 real animals + 25 imaginary
    creatures) with acoustically accurate parameters based on the inverse
    square law for animal size scaling.
*/
class FactoryPresets
{
public:
    //==============================================================================
    /**
        Get all factory presets

        Returns a vector of all 50 factory presets with complete parameter
        sets for each animal/creature type.

        @returns std::vector<PresetParameters> All factory presets
    */
    static std::vector<PresetParameters> getAllPresets();
};

//==============================================================================
/**
    Helper functions for preset management
*/
namespace PresetHelpers
{
    /**
        Find presets by animal name

        @param animalName The animal name to search for
        @returns std::vector<int> Indices of matching presets
    */
    std::vector<int> findByAnimalName (const std::string& animalName);

    /**
        Find presets by category

        @param category The category (bigcats, canines, bears, mythical, scifi)
        @returns std::vector<int> Indices of matching presets
    */
    std::vector<int> findByCategory (const std::string& category);

    /**
        Get preset category from index

        @param index The preset index (0-49)
        @returns std::string The category name
    */
    std::string getCategory (int index);

    /**
        Validate preset parameters

        @param preset The preset to validate
        @returns bool True if all parameters are valid
    */
    bool validatePreset (const PresetParameters& preset);
}
