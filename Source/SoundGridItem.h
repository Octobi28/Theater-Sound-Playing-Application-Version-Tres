/*
  ==============================================================================

    SoundGridItem.h
    Created: 26 Oct 2026 11:26:07am
    Author:  Zachary Cross

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Sounds.h"

//==============================================================================
/*
*/
class SoundGrid  : public juce::Component, public juce::AudioSource
{
public:
    SoundGrid();
    ~SoundGrid() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidth(int w);
    void makeList(std::vector<std::shared_ptr<Sound>>);
    void calcGrid();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources () override;
    

    
    class SoundGridItem : public juce::Component
    {
        public:
            SoundGridItem(std::shared_ptr<Sound>);

            void paint (juce::Graphics&) override;
            void resized() override;
            std::shared_ptr<Sound> getSound();
        private:
            std::shared_ptr<Sound> sound;
            juce::TextButton ppButton;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundGridItem)
    };
private:
    std::vector<std::unique_ptr<SoundGridItem>> sounds;
    int width;
    int cols;
    int rows;
    int itemWidth;
    const static int minWidth = 128;
    const static int itemHeight = 128;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundGrid)
};
