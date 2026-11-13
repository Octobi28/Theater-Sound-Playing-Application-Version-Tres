/*
  ==============================================================================

    Footer.cpp
    Created: 21 Oct 2026 9:30:11am
    Author:  Zachary Cross

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Footer.h"

//==============================================================================
Footer::Footer(MusicList* list, juce::AudioFormatManager& manager) : song{}, thumbnail{512, manager, thumbCache}, thumbCache{25}
{
    pop = true;
    ppButton.setImages(false, true, true, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 1.0, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 1, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 0.5, juce::Colours::grey);
    ppButton.onClick = [this, list](){ppClick(list);};
    addAndMakeVisible(ppButton);
    
    prev.setImages(false, true, true, juce::ImageFileFormat::loadFrom(BinaryData::prev_png, BinaryData::prev_pngSize), 1.0, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::prev_png, BinaryData::prev_pngSize), 1, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::prev_png, BinaryData::prev_pngSize), 0.5, juce::Colours::grey);
    prev.onClick = [this, list](){prevClick(list);};
    addAndMakeVisible(prev);
    
    next.setImages(false, true, true, juce::ImageFileFormat::loadFrom(BinaryData::next_png, BinaryData::next_pngSize), 1.0, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::next_png, BinaryData::next_pngSize), 1, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::next_png, BinaryData::next_pngSize), 0.5, juce::Colours::grey);
    next.onClick = [this, list](){nextClick(list);};
    addAndMakeVisible(next);
    
    song = list->getSelectedSound();
    if (song != nullptr){
        thumbnail.setSource(new juce::FileInputSource(song->file));
    }
    listBackup = list;
    
    list->setCallback([this](int i){callback(i);});
}

Footer::~Footer()
{
}

void Footer::paint (juce::Graphics& g)
{
    //1080x96, height more consistent than width.

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    if (song != nullptr){
        g.drawText (song->name, getLocalBounds().removeFromTop(20),
                    juce::Justification::centred, true);
    } else{
        song = listBackup->getSelectedSound();
        thumbnail.setSource(new juce::FileInputSource(song->file));
        repaint();
    }
    if (thumbnail.getNumChannels() != 0){
        g.setColour(juce::Colours::grey);
        auto rect = getLocalBounds().reduced(getWidth()/3, 5);
        rect.removeFromBottom(40);
        rect.removeFromTop(20);
        g.fillRect(rect.expanded(5, 5));
        g.setColour(juce::Colours::white);
        
        thumbnail.drawChannel(g, rect, 0, song->sound.getLengthInSeconds(), 0, 1.0f);
    }
}

void Footer::resized()
{
    auto area = getLocalBounds().reduced(getWidth()/3, 5).removeFromBottom(32);
    
    auto ppRect = juce::Rectangle<int>(0, 0, 32, 32);
    ppRect.setCentre(area.getCentre());
    ppButton.setBounds(ppRect);
    
    
    auto otherRect = juce::Rectangle<int>(0, 0, 32*5, 32);
    otherRect.setCentre(area.getCentre());
    prev.setBounds(otherRect.removeFromLeft(32));
    next.setBounds(otherRect.removeFromRight(32));
}

void Footer::ppClick(MusicList* list){
    swapPP();
    list->ppButton(pop);
}

void Footer::nextClick(MusicList* list){
    list->nextButton();
    song = list->getSelectedSound();
    repaint();
}
void Footer::prevClick(MusicList* list){
    list->prevButton();
    song = list->getSelectedSound();
    repaint();
}

void Footer::swapPP(){
    if(pop){
        ppButton.setImages(false, true, true, juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize), 1, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize), 0.5, juce::Colours::grey);
        pop = false;
    }
    else {
        ppButton.setImages(false, true, true, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 1.0, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 1, juce::Colours::transparentBlack, juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize), 0.5, juce::Colours::grey);
        pop = true;
    }
}

void Footer::callback(int state){
    switch (state) {
        case 0:
            swapPP();
            break;
        case 1:
            song = listBackup->getSelectedSound();
            thumbnail.setSource(new juce::FileInputSource(song->file));
            repaint();
            break;
    }
}
