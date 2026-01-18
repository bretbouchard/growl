cmake_minimum_required(VERSION 3.15)
project(growl VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE setup
set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../external/JUCE")
if(NOT EXISTS "${JUCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "JUCE not found at ${JUCE_DIR}")
endif()

add_subdirectory(${JUCE_DIR} JUCE)

# Growl Plugin - All 7 Formats as required by PLUGIN_ARCHITECTURE_CONTRACT
set(JUCE_FORMATS
    VST3
    AU
    CLAP
    LV2
    AUv3
    Standalone
)

# Plugin source files
set(PLUGIN_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GrowlPlugin.cpp
)

# Create the plugin with all formats
juce_add_plugin(growl
    PLUGIN_SRC ${PLUGIN_SRC}
    FORMAT ${JUCE_FORMATS}
    COMPANY_NAME "White Room Audio"
    PLUGIN_MANUFACTURER_CODE "WRA "
    PLUGIN_CODE "Grow"
    VERSION ${PROJECT_VERSION}
    PRODUCT_NAME "Growl"
    BUNDLE_ID "com.whiteroomaudio.growl"
    IS_SYNTH 1
    NEEDS_CURL false
    NEEDS_WEB_BROWSER false
)

# Link JUCE libraries
target_link_libraries(growl
    PRIVATE
        juce::juce_audio_plugin_client
        juce::juce_audio_utils
        juce::juce_dsp
)

# Include directories
target_include_directories(growl
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dsp
)

# DSP-only target for testing (no AudioProcessor wrapper)
add_library(growl_dsp STATIC
    include/dsp/NoiseGenerator.h
    include/dsp/GrowlDSP.h
)

target_link_libraries(growl_dsp
    PRIVATE
        juce::juce_audio_basics
        juce::juce_dsp
)

target_include_directories(growl_dsp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dsp
)

# Install targets for each format
install(TARGETS growl
    ARCHIVE DESTINATION plugins/dsp
    LIBRARY DESTINATION plugins/dsp
    RUNTIME DESTINATION plugins/dsp
)

# Install presets
install(DIRECTORY presets/
    DESTINATION presets
    FILES_MATCHING PATTERN "*.xml"
)

# Copy built plugins to their respective directories
install(CODE "
    # VST3
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/VST3/growl.vst3
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/vst/)

    # AU
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/AU/growl.component
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/au/)

    # CLAP
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/CLAP/growl.clap
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/clap/)

    # LV2
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/LV2/growl.lv2
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/lv2/)

    # AUv3
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/AUv3/growl.appex
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/auv3/)

    # Standalone
    file(COPY \${CMAKE_BINARY_DIR}/growl_artefacts/Standalone/growl.app
         DESTINATION ${CMAKE_SOURCE_DIR}/plugins/standalone/)
" COMPONENT Runtime)
