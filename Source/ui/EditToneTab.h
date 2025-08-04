/*
  ==============================================================================

    EditToneTab.h
    Created: 20 Aug 2024 2:34:06pm
    Author:  Giulio Zausa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class EditToneTab  : public juce::Component, public juce::Slider::Listener, public juce::Button::Listener, public juce::ComboBox::Listener
{
public:
    EditToneTab(Jv880_juceAudioProcessor&);
    ~EditToneTab() override;
    
    void updateValues();

    void visibilityChanged() override;
    void resized() override;
    void sliderValueChanged (juce::Slider*) override;
    void buttonClicked (juce::Button*) override;
    void buttonStateChanged (juce::Button*) override;
    void comboBoxChanged (juce::ComboBox*) override;

private:
    Jv880_juceAudioProcessor& audioProcessor;
    juce::ComboBox toneSelectionComboBox;
    juce::Label toneSelectionLabel;
    juce::ComboBox waveGroupComboBox;
    juce::Label waveGroupLabel;
    juce::Slider waveformSlider;
    juce::Label waveformLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditToneTab)
};
