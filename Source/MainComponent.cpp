#include "MainComponent.h"

//==============================================================================


MainComponent::MainComponent() : header{}, lSidebar{musicList}, rSidebar{soundGrid}, musicList{}, footer{&musicList, audioFormatManager}, musicViewport{"viewport for music lsiting its the viewport that lists the music in a vertical table of listed music with name and duration"}, soundGrid{}, soundViewport{"its the viewport for viewing the sounds so they display properly and work right and stuff"}, mainWorkingDirectory{juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("V3 Sound")}, mixer{}
{
    
    //initialize all main components
    addAndMakeVisible(header);
    addAndMakeVisible(footer);
    addAndMakeVisible(lSidebar);
    addAndMakeVisible(rSidebar);
    
    addAndMakeVisible(musicViewport);
    musicViewport.setViewedComponent(&musicList, false);
    
    addAndMakeVisible(soundViewport);
    soundViewport.setViewedComponent(&soundGrid, false);
    
    
    setSize (1080, 720);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    
    //set up files
    if(!mainWorkingDirectory.exists()){
        mainWorkingDirectory.createDirectory();
    }
    if(!mainWorkingDirectory.getChildFile("sound").exists()){
        mainWorkingDirectory.getChildFile("sound").createDirectory();
    }
    if(!mainWorkingDirectory.getChildFile("music").exists()){
        mainWorkingDirectory.getChildFile("music").createDirectory();
    }
    
    //add component audio
    mixer.addInputSource(&musicList, false);
    mixer.addInputSource(&soundGrid, false);
    
    audioFormatManager.registerBasicFormats();
    
    soundGrid.makeList(makeSoundVector(mainWorkingDirectory.getChildFile("sound")));
    musicList.makeList(makeSoundVector(mainWorkingDirectory.getChildFile("music")));
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    mixer.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    if (bufferToFill.buffer->getNumChannels() == 0)
    {
        std::cout << "uh oh! no channels :(";
        return;
    }
    mixer.getNextAudioBlock (bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    mixer.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    //set the sizes of everything
    auto area = getLocalBounds();
    header.setBounds(area.removeFromTop(48));
    footer.setBounds(area.removeFromBottom(96));
    lSidebar.setBounds(area.removeFromLeft(96));
    rSidebar.setBounds(area.removeFromRight(96));
    
    int msuicx = area.getWidth()/2;
    
    musicViewport.setBounds(area.removeFromLeft(msuicx));
    musicList.setWidth(msuicx);
    
    soundViewport.setBounds(area);
    soundGrid.setWidth(soundViewport.getWidth());
}

std::vector<std::shared_ptr<Sound>> MainComponent::makeSoundVector(juce::File folder){
    std::vector<std::shared_ptr<Sound>> sounds;
    for (const auto& entry : juce::RangedDirectoryIterator (folder, true, "*", juce::File::findFiles)) {
        if (audioFormatManager.findFormatForFileExtension(entry.getFile().getFileExtension()) != nullptr)
            sounds.emplace_back(new Sound(entry.getFile(), audioFormatManager));
    }
    return sounds;
}
