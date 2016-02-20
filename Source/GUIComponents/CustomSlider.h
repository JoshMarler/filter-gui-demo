/*
  ==============================================================================

    ParameterSlider.h
    Created: 17 Feb 2016 9:58:49pm
    Author:  Joshua Marler

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

#ifndef CUSTOMSLIDER_H_INCLUDED
#define CUSTOMSLIDER_H_INCLUDED

class CustomSlider   : public Slider,
                       private Timer
{
public:
    CustomSlider(AudioProcessorParameter& p);
    
    void valueChanged() override;
    void timerCallback() override;
   
    void startedDragging() override;
    void stoppedDragging() override;
  
    double getValueFromText (const String& text) override;
    String getTextFromValue (double value) override;
    
    void updateSliderPos();

private:
    
    AudioProcessorParameter& param;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};



#endif  // CUSTOMSLIDER_H_INCLUDED
