/*
  ==============================================================================

    EditToneTab.cpp
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EditToneTab.h"
#include "../dataStructures.h"

//==============================================================================
EditToneTab::EditToneTab(Jv880_juceAudioProcessor& p) :
  audioProcessor (p)
{
    addAndMakeVisible(toneSelectionLabel);
    toneSelectionLabel.setText ("Wave Group", juce::dontSendNotification);
    toneSelectionLabel.attachToComponent (&toneSelectionComboBox, true);
    addAndMakeVisible (toneSelectionComboBox);
    toneSelectionComboBox.addListener (this);
    toneSelectionComboBox.addItem ("Tone A", 1);
    toneSelectionComboBox.addItem ("Tone B", 2);
    toneSelectionComboBox.addItem ("Tone C", 3);
    toneSelectionComboBox.addItem ("Tone D", 4);
    
    
    addAndMakeVisible(waveGroupLabel);
    waveGroupLabel.setText ("Wave Group", juce::dontSendNotification);
    waveGroupLabel.attachToComponent (&waveGroupComboBox, true);
    addAndMakeVisible (waveGroupComboBox);
    waveGroupComboBox.addListener (this);
    waveGroupComboBox.addItem ("Internal", 1);
    waveGroupComboBox.addItem ("Expansion", 2);
    
    addAndMakeVisible(waveformLabel);
    waveformLabel.setText ("Waveform", juce::dontSendNotification);
    waveformLabel.attachToComponent (&waveformSlider, true);
    addAndMakeVisible (waveformSlider);
    waveformSlider.setRange (0, 255);
    waveformSlider.addListener (this);
}

EditToneTab::~EditToneTab()
{
}

void EditToneTab::updateValues()
{
    Patch* patch = (Patch*) audioProcessor.status.patch;
    Tone tone = patch->tones[toneSelectionComboBox.getSelectedItemIndex()];
    waveGroupComboBox.setSelectedItemIndex((tone.flags & 0x3), juce::dontSendNotification);
    waveformSlider.setValue(tone.waveNumber & 0xff, juce::dontSendNotification);
}

void EditToneTab::visibilityChanged()
{
    updateValues();
}

void EditToneTab::resized()
{
    auto top = 30;
    auto sliderLeft1 = 120;
    auto width = getWidth() / 2 - sliderLeft1 - 20;
    auto height = 32;
    auto groupMargin = 24;
    toneSelectionComboBox.setBounds(sliderLeft1, top + height * 0 + groupMargin * 0, width, height);
    waveGroupComboBox.setBounds(sliderLeft1, top + height * 2 + groupMargin * 0, width, height);
    waveformSlider.setBounds(sliderLeft1, top + height * 3 + groupMargin * 0, width, height);
}

void EditToneTab::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &waveformSlider)
    {
        uint8_t toneNum = toneSelectionComboBox.getSelectedItemIndex() - 1;
        uint32_t address = 0x1A + 0x01 + (0x54 * toneNum);
        uint8_t value = waveformSlider.getValue();
        audioProcessor.sendSysexParamChange(address, value);
    }
}

void EditToneTab::buttonClicked (juce::Button* button)
{
}

void EditToneTab::buttonStateChanged (juce::Button* button)
{
}

void EditToneTab::comboBoxChanged (juce::ComboBox* button)
{
    if (button == &toneSelectionComboBox)
    {
        updateValues();
    }
}
