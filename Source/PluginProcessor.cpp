/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlugInAudioProcessor::PlugInAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

PlugInAudioProcessor::~PlugInAudioProcessor()
{
}

//==============================================================================
const String PlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PlugInAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String PlugInAudioProcessor::getProgramName (int index)
{
    return {};
}

void PlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PlugInAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	int fs = 44100;
	IIRFilter lowshelfL, lowshelfR, highshelfL, highshelfR, parametricL, parametricR;
	
	float *dataLeft = buffer.getWritePointer(0);
	float *dataRight = buffer.getWritePointer(1);
	
	int nSamples = buffer.getNumSamples();
	IIRCoefficients icls = IIRCoefficients::makeLowShelf(fs,freqls, 1, gainls);
	IIRCoefficients ichs = IIRCoefficients::makeHighShelf(fs, freqhs, 1, gainhs);
	IIRCoefficients icpar = IIRCoefficients::makePeakFilter(fs, freqpar, q, gainpar);
	
	lowshelfL.setCoefficients(icls);
	lowshelfR.setCoefficients(icls);

	lowshelfL.processSamples(dataLeft, nSamples);
	lowshelfR.processSamples(dataRight, nSamples);

	parametricL.setCoefficients(icpar);
	parametricR.setCoefficients(icpar);

	parametricL.processSamples(dataLeft, nSamples);
	parametricR.processSamples(dataRight, nSamples);

	highshelfL.setCoefficients(ichs);
	highshelfL.setCoefficients(ichs);

	highshelfL.processSamples(dataLeft, nSamples);
	highshelfL.processSamples(dataRight, nSamples);

}

//==============================================================================
bool PlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PlugInAudioProcessor::createEditor()
{
    return new PlugInAudioProcessorEditor (*this);
}

//==============================================================================
void PlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PlugInAudioProcessor();
}

