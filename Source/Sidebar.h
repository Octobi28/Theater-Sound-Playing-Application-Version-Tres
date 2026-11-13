/*
  ==============================================================================

    Sidebar.h
    Created: 21 Oct 2026 9:30:30am
    Author:  Zachary Cross

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "sound_meter/sound_meter.h"
#include "SoundGridItem.h"
#include "MusicList.h"

//==============================================================================
/*
*/
class Sidebar  : public juce::Component
{
public:
    Sidebar(juce::AudioSource&);
    ~Sidebar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    sd::SoundMeter::MetersComponent  meter;
    juce::AudioSource* monitored;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sidebar)
};
