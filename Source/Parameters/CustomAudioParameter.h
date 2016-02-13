/*
  ==============================================================================

    CustomAudioParameter.h
    Created: 19 Jun 2015 7:27:04pm
    Author:  Joshua Marler

  ==============================================================================
*/

#ifndef CustomAudioParameter_H_INCLUDED
#define CustomAudioParameter_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class CustomAudioParameter : public AudioProcessorParameter

{

public:
    
    CustomAudioParameter(const String& paramName, int initParameterType);
    
    CustomAudioParameter(const String& paramName, int initParameterType, std::function<void(float)> initSetValueCallback);
    
    ~CustomAudioParameter();
    
    float getValue() const override;
    void setValue(float newValue) override;
    
    
    /** Functions for setting the custom min and max values for use in custom parameter type calculations.
        If using any param type other than Regular_Float_Param these should be called before use/right after construction.
     
        For example for a Volt_Octave_Param customMinValue would be the mminFrequencyLimit and customMaxValue the maxFrequencyLimit
        in calcValueVoltOctaveExp(float minFrequencyLimit, float maxFrequencyLimit, float paramValue).
    */
    void setCustomMinValue(float newCustomMinValue);
    void setCustomMaxValue(float newCustomMaxValue);
    
    
    float getDefaultValue() const override;
    String getName(int maximumStringLength) const override;
    String getLabel() const override;
    float getValueForText (const String& text) const override;
    
    /** Maps 0.0 - 1.0 values required by host into relative frequency hz values within min - max limits.
        Code original from Will Pirkle - see ...
    */
    float calcValueVoltOctaveExp(float minFrequencyLimit, float maxFrequencyLimit, float paramValue);
    
    String getText(float value, int = 0 /*Maximum String Length - default value provided/optional*/) const override;
    
    
    /** Custom parameter types - different types will have different calculations/code for setting and using the customValue member.
        The customValue member can then be passed to the setValueCallback function.
     */
    enum ParameterTypes
    {
        Regular_Float_Param = 0,
        Volt_Octave_Param
    };
    
private:
    
    //Wrap these up as std::atomic types and then call atmoic load / store
    float defaultValue = 0.5;
    float value = 0.0;
    
    float customValue = 0.0;
    float customMinValue = 0.0;
    float customMaxValue = 0.0;
    
    int parameterType;
    
    String name;
    
    std::function<void(float)> setValueCallback = nullptr;
};




#endif  // CustomAudioParameter_H_INCLUDED
