/*
  ==============================================================================

    MusicList.cpp
    Created: 22 Oct 2026 2:22:01pm
    Author:  Zachary Cross

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicList.h"

//==============================================================================
int MusicList::selected = 0;
bool MusicList::playing = false;

MusicList::MusicList() : music{}, width{}
{
}

MusicList::~MusicList()
{
}

void MusicList::setCallback(std::function<void(int)> cback){
    callback = cback;
}

void MusicList::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);
}

void MusicList::resized()
{
    //sizes everything into place
    auto area = getLocalBounds();
    for (int i = 0; i < music.size(); i++) {
        music[i].get()->setBounds(area.removeFromTop(rowHeight));
    }
}

void MusicList::setWidth(int w){
    //sets width (and height for rows) of the component
    width = w;
    setSize(width, (int)music.size() * rowHeight);
}

void MusicList::makeList(std::vector<std::shared_ptr<Sound>> s){
    //makes all the components for displaying a new table based on given vector
    if (music.size() != 0){
        for (int i = 0; i < music.size(); i++) {
            removeChildComponent(music[i].get());
        }
        music.clear();
        mixer.removeAllInputs();
    }
    
    for (int i = 0; i < s.size(); i++) {
        music.emplace_back(new Line(s[i], i));
        addAndMakeVisible(music.back().get());
        mixer.addInputSource(music.back().get()->getSound().get(), false);
        music.back().get()->getSound()->sound.addChangeListener(this);
    }
    setWidth(width);
}

//=======================================================

void MusicList::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void MusicList::getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill){
    mixer.getNextAudioBlock(bufferToFill);
    if (!playing){
        bufferToFill.clearActiveBufferRegion();
    }
}
void MusicList::releaseResources (){
    mixer.removeAllInputs();
    for (int i = 0; i < music.size(); i++){
        music[i]->getSound()->releaseResources();
    }
    mixer.releaseResources();
}

//=======================================================

void MusicList::ppButton(bool pop){
    if (!pop){
        music[selected]->getSound()->sound.start();
    }
    else{
        music[selected]->getSound()->sound.stop();
    }
    
}

void MusicList::prevButton(){
    modSelected(-1, false);
}

void MusicList::nextButton(){
    modSelected(1, false);
}

void MusicList::changeListenerCallback (juce::ChangeBroadcaster* source){
    for (int i = 0; i < music.size(); i++){
        if (&music[i]->getSound()->sound == source){
            playing = music[i]->getSound()->sound.isPlaying();
            if (!playing){
                modSelected(1, false);
                callback(0);
                callback(1);
            }
        }
    }
}

//=======================================================

void MusicList::modSelected(int num, bool absolute){
    music[selected]->getSound()->sound.stop();
    music[selected]->getSound()->sound.setPosition(0.0);
    if (absolute && num >= 0 && num < music.size()){
        if (num < 0){
            num = 0;
        }
        if (num >= music.size()){
            num = (int)music.size() - 1;
        }
        selected = num;
    }
    else{
        selected += num;
        if (selected >= (int)music.size()){
            selected = 0;
        }
        if (selected < 0){
            selected = ((int)music.size()) - 1;
        }
    }
    music[selected]->getSound()->sound.setPosition(0.0);
    repaint();
}

MusicList::Line::Line(std::shared_ptr<Sound> m, int n) : music{m}, num{n}{}

void MusicList::Line::paint(juce::Graphics& g){
    //draw each individual track on the table
    g.setColour(juce::Colours::purple);
    if (num % 2 == 0)
        g.setColour(juce::Colours::gold);
    if (num == selected)
        g.setColour(juce::Colours::grey);
    
    g.fillAll();
    
    g.setColour(juce::Colours::white);
    g.setFont(fontSize);
    
    g.drawText((juce::String)(num+1) + ".", getLocalBounds().reduced(xPadding, yPadding), juce::Justification::left);
    g.drawText(music->name, getLocalBounds(), juce::Justification::centred, true);
    
    juce::String sStr {(juce::String)(floor(music->duration))};
    if (sStr.length() == 1)
        sStr = "0" + sStr;
    
    juce::String durstr {(juce::String)floor(music->duration/60) + ":" + sStr};
    g.drawText(durstr, getLocalBounds().reduced(xPadding, yPadding), juce::Justification::right);
}

std::shared_ptr<Sound> MusicList::Line::getSound(){
    return music;
}

std::shared_ptr<Sound> MusicList::getSelectedSound(){
    if (music.size() > selected){
        return music[selected]->getSound();
    }
    return nullptr;
}
