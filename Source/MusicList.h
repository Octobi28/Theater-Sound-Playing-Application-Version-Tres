/*
  ==============================================================================

    MusicList.h
    Created: 22 Oct 2026 2:22:01pm
    Author:  Zachary Cross

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Sounds.h"

//==============================================================================
/*
*/
class MusicList  : public juce::Component, public juce::AudioSource, public juce::ChangeListener
{
public:
    
    MusicList();
    ~MusicList() override;
    void setCallback(std::function<void(int)> cback);

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidth(int w);
    void makeList(std::vector<std::shared_ptr<Sound>>);
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources () override;
    
    void ppButton(bool);
    void prevButton();
    void nextButton();
    
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    
    void modSelected(int, bool);
    std::shared_ptr<Sound> getSelectedSound();

private:
    
    class Line : public juce::Component
    {
    public:
        
        Line(std::shared_ptr<Sound> m, int n);

        void paint (juce::Graphics&) override;
        std::shared_ptr<Sound> getSound();
        
    private:
        std::shared_ptr<Sound> music;
        int num;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Line)
    };
    
    
    
    std::vector<std::unique_ptr<MusicList::Line>> music;
    int width;
    juce::AudioFormatManager audioFormatManager;
    juce::MixerAudioSource mixer;
    std::function<void(int)> callback;
    static int selected;
    static bool playing;
    
    static const int rowHeight = 32;
    static const int fontSize = 14;
    static const int xPadding = 5;
    static const int yPadding = 0;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicList)
};
