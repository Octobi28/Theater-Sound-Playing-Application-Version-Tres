#pragma once

#include <JuceHeader.h>
#include "Header.h"
#include "Footer.h"
#include "Sidebar.h"
#include "MusicList.h"
#include "SoundGridItem.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    std::vector<std::shared_ptr<Sound>> makeSoundVector(juce::File folder);
    //==============================================================================
    // Your private member variables go here...
    Header header;
    Sidebar lSidebar;
    Sidebar rSidebar;
    MusicList musicList;
    Footer footer;
    juce::Viewport musicViewport;
    SoundGrid soundGrid;
    juce::Viewport soundViewport;
    juce::File mainWorkingDirectory;
    juce::AudioFormatManager audioFormatManager;
    juce::MixerAudioSource mixer;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
