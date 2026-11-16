/*
  ==============================================================================

    Sounds.h
    Created: 22 Oct 2026 11:30:58am
    Author:  Zachary Cross

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>

struct Sound : juce::AudioSource {
    public:
    
    Sound(juce::File file, juce::AudioFormatManager& formatManager) : name{file.getFileNameWithoutExtension()}
    {
        this->file = file;
        auto* reader = formatManager.createReaderFor(file);
        newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
        sound.setSource(newSource.get(), 0, nullptr, reader->sampleRate, 2);
        duration = sound.getLengthInSeconds();
        
        if (isSystemPrepared && savedBlockSize > 0 && savedSampleRate > 0.0)
        {
            sound.prepareToPlay (savedBlockSize, savedSampleRate);
        }
    }
    ~Sound() override {
        sound.setSource(nullptr);
    }
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override{
        savedBlockSize = samplesPerBlockExpected;
        savedSampleRate = sampleRate;
        isSystemPrepared = true;
        
        sound.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
    void getNextAudioBlock (const juce::AudioSourceChannelInfo &bufferToFill) override{
        if (newSource.get() == nullptr || !sound.isPlaying())
        {
                bufferToFill.clearActiveBufferRegion();
                return;
        }
        std::cout << "sound " << name << " playing at position " << sound.getCurrentPosition() << "\n";
        sound.getNextAudioBlock(bufferToFill);
    }
    void releaseResources () override{sound.releaseResources();}
    void print(){std::cout << name;}
    
    juce::String name;
    double duration;
    std::unique_ptr<juce::AudioFormatReaderSource> newSource;
    juce::AudioTransportSource sound;
    juce::File file;
    
    int savedBlockSize;
    int savedSampleRate;
    bool isSystemPrepared = false;
};
