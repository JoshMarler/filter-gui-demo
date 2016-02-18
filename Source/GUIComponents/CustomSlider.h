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
    
/*
    
    JWM - Development note 
    Change this class to FloatParamSlider
    Pass in a std::function<void(float)> paramUpdateCallbacks and std::function<void(Graphics &g) guiUpdateCallbacks>. 
    Or - Pass in an AudioProcessorParameter object/array and also a Component object/array and call their set value and paint methods.
 
*/
public:
    CustomSlider (AudioProcessorParameter& p);
    
    void valueChanged() override;
    void timerCallback() override;
   
    void startedDragging() override;
    void stoppedDragging() override;
    
    double getValueFromText (const String& text) override;
    String getTextFromValue (double value) override;
    
    void updateSliderPos();

private:
    
    //JWM - Note maybe have a std::vector of parameter references and a std::vector of component references to update on change.
    //That way a slider can affect multiple parameters and multiple external GUI components if needed.
    //Have a function addParameterListener and a function addComponentListener. 
    //std::vector<AudioProcessorParameter&> parameters;
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};



#endif  // CUSTOMSLIDER_H_INCLUDED
