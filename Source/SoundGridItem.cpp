/*
  ==============================================================================

    SoundGridItem.cpp
    Created: 26 Oct 2026 11:26:07am
    Author:  Zachary Cross

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SoundGridItem.h"

//==============================================================================
SoundGrid::SoundGrid()
{
}

SoundGrid::~SoundGrid()
{
}

void SoundGrid::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // draw some placeholder text
}

void SoundGrid::resized()
{
    //on size change, draw everything at the right size
    calcGrid();
    auto area = getLocalBounds();
    int soundIndex = 0;
    for (int i = 0; i < rows; i++) {
        auto rowArea = area.removeFromTop(itemHeight);
        for (int x = 0; x < cols; x++) {
            if (soundIndex >= sounds.size()){
                break;
            }
            sounds[soundIndex]->setBounds(rowArea.removeFromLeft(itemWidth));
            soundIndex++;
        }
    }
}

void SoundGrid::setWidth(int w){
    //sets width (and hieght of rows) of component
    width = w;
    setSize(w, rows*itemHeight);
    
}

void SoundGrid::makeList(std::vector<std::shared_ptr<Sound>> s){
    //turns a vector of sounds in a vector of components
    if (sounds.size() != 0){
        for (int i = 0; i < sounds.size(); i++) {
            removeChildComponent(sounds[i].get());
        }
        sounds.clear();
    }
    
    for (int i = 0; i < s.size(); i++) {
        sounds.emplace_back(new SoundGridItem(s[i]));
        addAndMakeVisible(sounds.back().get());
    }
    calcGrid();
}

void SoundGrid::calcGrid(){
    //helper function to calculate the size of each button component
    cols = floor(getWidth()/minWidth);
    itemWidth = getWidth()/(float)cols;
    if (!sounds.empty())
        rows = ceil(sounds.size()/(float)cols);
    else
        rows = 0;
    setWidth(width);
}

void SoundGrid::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    
}
void SoundGrid::getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill){
    bufferToFill.clearActiveBufferRegion();
}
void SoundGrid::releaseResources (){
    for (int i = 0; i < sounds.size(); i++){
        sounds[i]->getSound()->releaseResources();
    }
}

SoundGrid::SoundGridItem::SoundGridItem(std::shared_ptr<Sound> s) : sound{s}, ppButton{"Play"}{
    addAndMakeVisible(ppButton);
}

void SoundGrid::SoundGridItem::paint(juce::Graphics &g){
    //draw the buttons
    g.fillAll(juce::Colours::greenyellow);
    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds());
    g.setColour(juce::Colours::white);
    g.drawText(sound->name, getLocalBounds(), juce::Justification::centred);
}

void SoundGrid::SoundGridItem::resized(){
    ppButton.setBounds(getLocalBounds().removeFromBottom(48));
}

std::shared_ptr<Sound> SoundGrid::SoundGridItem::getSound(){
    return sound;
}
