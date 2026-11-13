/*
  ==============================================================================

    Footer.h
    Created: 21 Oct 2026 9:30:11am
    Author:  Zachary Cross

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MusicList.h"

//==============================================================================
/*
*/
class Footer  : public juce::Component
{
public:
    Footer(MusicList* list, juce::AudioFormatManager& manager);
    ~Footer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void ppClick(MusicList*);
    void nextClick(MusicList*);
    void prevClick(MusicList*);
    
    void callback(int state);
    
    void swapPP();

private:
    juce::ImageButton prev;
    juce::ImageButton ppButton;
    juce::ImageButton next;
    std::shared_ptr<Sound> song;
    MusicList* listBackup;
    bool pop;
    juce::AudioThumbnail thumbnail;
    juce::AudioThumbnailCache thumbCache;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Footer)
};
