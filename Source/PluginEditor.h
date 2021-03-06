/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class PlugInAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    PlugInAudioProcessorEditor (PlugInAudioProcessor&);
    ~PlugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PlugInAudioProcessor& processor;


	Slider GainLowShelf, FreqLowShelf, GainHighShelf, FreqHighShelf, GainParametric, FreqParametric, Q;
	Label GLSlabel, FLSlabel, GHSlabel, FHSlabel, GPlabel, FPlabel, Qlabel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlugInAudioProcessorEditor)
};
