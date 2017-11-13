/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlugInAudioProcessorEditor::PlugInAudioProcessorEditor (PlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (480, 570);

	addAndMakeVisible(GainLowShelf);
	addAndMakeVisible(FreqLowShelf);
	addAndMakeVisible(GainHighShelf);
	addAndMakeVisible(FreqHighShelf);
	addAndMakeVisible(GainParametric);
	addAndMakeVisible(FreqParametric);
	addAndMakeVisible(Q);

	GainLowShelf.addListener(this);
	GainLowShelf.setSliderStyle(Slider::SliderStyle::Rotary);
	GainLowShelf.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	GainLowShelf.setTextValueSuffix(" dB");
	GainLowShelf.setRange(-24.0, 24.0, 1.0);
	GainLowShelf.setValue(0.0);
	
	FreqLowShelf.addListener(this);
	FreqLowShelf.setSliderStyle(Slider::SliderStyle::Rotary);
	FreqLowShelf.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20 );
	FreqLowShelf.setTextValueSuffix(" Hz");
	FreqLowShelf.setRange(50.0, 200.0, 25.0);
	FreqLowShelf.setValue(50.0);
	FreqLowShelf.setSkewFactor(2, false);

	GainParametric.addListener(this);
	GainParametric.setSliderStyle(Slider::SliderStyle::Rotary);
	GainParametric.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	GainParametric.setTextValueSuffix(" dB");
	GainParametric.setRange(-24.0, 24.0, 1.0);
	GainParametric.setValue(0.0);

	FreqParametric.addListener(this);
	FreqParametric.setSliderStyle(Slider::SliderStyle::Rotary);
	FreqParametric.setTextBoxStyle(Slider::TextBoxBelow, true , 80, 20);
	FreqParametric.setTextValueSuffix(" Hz");
	FreqParametric.setRange(500.0, 12000.0, 500.0);
	FreqParametric.setValue(500.0);
	FreqParametric.setSkewFactor(2, false);

	Q.addListener(this);
	Q.setSliderStyle(Slider::SliderStyle::Rotary);
	Q.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	Q.setRange(0.5, 2.0, 0.1);
	Q.setValue(1.0);

	GainHighShelf.addListener(this);
	GainHighShelf.setSliderStyle(Slider::SliderStyle::Rotary);
	GainHighShelf.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	GainHighShelf.setTextValueSuffix(" dB");
	GainHighShelf.setRange(-24.0, 24.0, 1.0);
	GainHighShelf.setValue(0.0);

	FreqHighShelf.addListener(this);
	FreqHighShelf.setSliderStyle(Slider::SliderStyle::Rotary);
	FreqHighShelf.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
	FreqHighShelf.setTextValueSuffix(" Hz");
	FreqHighShelf.setRange(8000.0, 18000.0, 1000.0);
	FreqHighShelf.setValue(8000.0);
	FreqHighShelf.setSkewFactor(2, false);

	addAndMakeVisible(GLSlabel);
	GLSlabel.setText("Low Shelf Gain", dontSendNotification);
	GLSlabel.attachToComponent(&GainLowShelf, false);

	addAndMakeVisible(FLSlabel);
	FLSlabel.setText("Low Shelf Frequency", dontSendNotification);
	FLSlabel.attachToComponent(&FreqLowShelf, false);

	addAndMakeVisible(GPlabel);
	GPlabel.setText("Parametric Gain", dontSendNotification);
	GPlabel.attachToComponent(&GainParametric, false);

	addAndMakeVisible(FPlabel);
	FPlabel.setText("Parametric Frequency", dontSendNotification);
	FPlabel.attachToComponent(&FreqParametric, false);

	addAndMakeVisible(Qlabel);
	Qlabel.setText("Parametric Q", dontSendNotification);
	Qlabel.attachToComponent(&Q, false);

	addAndMakeVisible(GHSlabel);
	GHSlabel.setText("High Shelf Gain", dontSendNotification);
	GHSlabel.attachToComponent(&GainHighShelf, false);

	addAndMakeVisible(FHSlabel);
	FHSlabel.setText("High Shelf Frequency", dontSendNotification);
	FHSlabel.attachToComponent(&FreqHighShelf, false);
}

PlugInAudioProcessorEditor::~PlugInAudioProcessorEditor()
{
}

//==============================================================================
void PlugInAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    
}

void PlugInAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	
	const int KnobWidth = 150;
	const int KnobHeight = 150;

	GainLowShelf.setBounds(0, 30, KnobWidth, KnobHeight);
	FreqLowShelf.setBounds(0, KnobHeight + 60, KnobWidth, KnobHeight);
	GainParametric.setBounds(KnobWidth + 10, 30, KnobWidth, KnobHeight);
	FreqParametric.setBounds(KnobWidth + 10, KnobHeight + 60, KnobWidth, KnobHeight);
	Q.setBounds(KnobWidth + 10, 2*KnobHeight + 90, KnobWidth, KnobHeight);
	GainHighShelf.setBounds(2*KnobWidth + 20, 30, KnobWidth, KnobHeight);
	FreqHighShelf.setBounds(2*KnobWidth + 20, KnobHeight + 60, KnobWidth, KnobHeight);
}

void PlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
	if (slider == &GainLowShelf) {
		processor.gainls = pow(10,GainLowShelf.getValue()/20);
	}
	else if (slider == &FreqLowShelf) {
		processor.freqls = FreqLowShelf.getValue();
	}
	else if (slider == &GainHighShelf) {
		processor.gainhs = pow(10, GainHighShelf.getValue() / 20);
	}
	else if (slider == &FreqHighShelf) {
		processor.freqhs = FreqHighShelf.getValue();
	}
	else if (slider == &GainParametric) {
		processor.gainpar = pow(10, GainParametric.getValue() / 20);
	}
	else if (slider == &FreqParametric) {
		processor.freqpar = FreqParametric.getValue();
	}
	else if (slider == &Q) {
		processor.q = Q.getValue();
	}
}

