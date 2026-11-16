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

bool SoundGrid::playing = false;

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
        mixer.removeAllInputs();
    }
    
    for (int i = 0; i < s.size(); i++) {
        sounds.emplace_back(new SoundGridItem(s[i]));
        addAndMakeVisible(sounds.back().get());
        mixer.addInputSource(sounds.back().get()->getSound().get(), false);
        sounds.back().get()->getSound()->sound.addChangeListener(this);
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

void SoundGrid::changeListenerCallback (juce::ChangeBroadcaster* source){
    for (int i = 0; i < sounds.size(); i++){
        if (&sounds[i]->getSound()->sound == source){
            playing = sounds[i]->getSound()->sound.isPlaying();
            if (!playing){
                std::cout << "got callback to stop sound!\n";
                sounds[i]->swapPP();
            }
        }
    }
}

//=============================================================================================

void SoundGrid::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void SoundGrid::getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill){
    mixer.getNextAudioBlock(bufferToFill);
    if (!playing){
        bufferToFill.clearActiveBufferRegion();
    }
}
void SoundGrid::releaseResources (){
    mixer.removeAllInputs();
    for (int i = 0; i < sounds.size(); i++){
        sounds[i]->getSound()->releaseResources();
    }
    mixer.releaseResources();
}

//=============================================================================================

SoundGrid::SoundGridItem::SoundGridItem(std::shared_ptr<Sound> s) : sound{s}, ppButton{"Play"}{
    addAndMakeVisible(ppButton);
    ppButton.onClick = [this](){ppClick();};
    pop = true;
    startPos = 0.0;
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

void SoundGrid::SoundGridItem::ppClick(){
    swapPP();
    if (!pop){
        sound->sound.setPosition(startPos);
        sound->sound.start();
        std::cout << "starting sound\n";
    }
    else {
        sound->sound.stop();
        std::cout << "stopping sound\n";
    }
    
}

void SoundGrid::SoundGridItem::swapPP(){
    if(pop){
        ppButton.setButtonText("Pause");
        pop = false;
    }
    else {
        ppButton.setButtonText("Play");
        pop = true;
    }
    std::cout << "Is button in ready to play state?: " << pop << "\n";
}
