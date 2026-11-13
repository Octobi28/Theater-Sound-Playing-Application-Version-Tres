/*
  ==============================================================================

    Sidebar.cpp
    Created: 21 Oct 2026 9:30:30am
    Author:  Zachary Cross

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Sidebar.h"


//==============================================================================
Sidebar::Sidebar(juce::AudioSource &mon) : meter{}, monitored(&mon)
{
    //set up the meter
    sd::SoundMeter::Options options{};
    options.useMinimalMode = false;
    meter.setOptions(options);
    meter.setChannelFormat(juce::AudioChannelSet::stereo());
    meter.setMeterSegments({ // From bottom of the meter (0.0f) to the half. Displaying -60 dB up to -18 dB.
        { { -60.0f, -18.0f }, { 0.0f, 0.5f }, juce::Colours::green, juce::Colours::green },
        // From half of the meter to almost the top (0.9f). Displaying -18 dB up to -3 dB.
        { { -18.0f, -3.0f }, { 0.5f, 0.90f }, juce::Colours::green, juce::Colours::yellow },
        // From almost the top to the top of the meter (1.0f). Displaying -3 dB up to 0 dB.
        { { -3.0f, 0.0f }, { 0.90f, 1.0f }, juce::Colours::yellow, juce::Colours::red } });
    addAndMakeVisible(meter);
    
}

Sidebar::~Sidebar()
{
}

void Sidebar::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Sidebar", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Sidebar::resized()
{
    // set the bounds of the meter
    meter.setBounds(getLocalBounds());
}
