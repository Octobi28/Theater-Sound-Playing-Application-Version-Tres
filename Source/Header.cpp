/*
  ==============================================================================

    Header.cpp
    Created: 19 Oct 2026 2:03:38pm
    Author:  Zachary Cross

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Header.h"

//==============================================================================
Header::Header()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    //draw the basic background

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 8.0f, 4.0f);
    
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Header", getLocalBounds(),
                juce::Justification::centred, true);
}

void Header::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
