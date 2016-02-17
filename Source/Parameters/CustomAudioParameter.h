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

/*
    Modified parameter class with some basic added extra's like ability to specify a callback funtion using std::function to be 
    called whenever parameter value changes. Class also includes a volt octave conversion function usefull for analogue style volt
    octave controls for filter cutoff knobs etc. Volt octave mapping function pinched with permission of Mr Will Pirkle -
    Will probably build out this class in future versions and may consider moving code like the volt octave mapping to a utilities
    library/class.
 */
class CustomAudioParameter : public AudioProcessorParameterWithID
{

public:
    
    CustomAudioParameter(String parameterID, String parameterName, int initParameterType);
    
    //initSetValueCallback is a callback function you can specify (using a lambda etc) that will be called every time the parameter value changes.
    CustomAudioParameter(String parameterID, String parameterName, int initParameterType, std::function<void(float)> initSetValueCallback);
    
    ~CustomAudioParameter();
    
    float getValue() const override;
    void setValue(float newValue) override;
    
    
    /** 
        Functions for setting the custom min and max values for use in custom parameter type calculations.
        If using any param type other than Regular_Float_Param these should be called before use
        righ after construction.
        For example for a Volt_Octave_Param customMinValue would be the minFrequencyLimit
        and customMaxValue the maxFrequencyLimit in calcValueVoltOctaveExp(float minFrequencyLimit, float maxFrequencyLimit, float paramValue).
    */
    void setCustomMinValue(float newCustomMinValue);
    void setCustomMaxValue(float newCustomMaxValue);
    
    
    float getDefaultValue() const override;
    String getName(int maximumStringLength) const override;
    String getLabel() const override;
    float getValueForText (const String& text) const override;
    
    /** 
        Maps 0.0 - 1.0 values required by host into relative frequency hz values within min - max limits.
        Code originally from Will Pirkle - see ...
    */
    float calcValueVoltOctaveExp(float minFrequencyLimit, float maxFrequencyLimit, float paramValue);
    
    String getText(float value, int = 0 /*Maximum String Length - default value provided/optional*/) const override;
    
    
    /** 
        Custom parameter types - different types will have different calculations/code for setting and using the customValue member.
        The customValue member can then be passed to the setValueCallback function.
     */
    enum ParameterTypes
    {
        Regular_Float_Param = 0,
        Volt_Octave_Param
    };
    
private:
    
    float defaultValue = 0.5;
    
    //Using std::atomic for the host/GUI changeable value to stop any data race conditions etc. As per Timur's talk.
    //The gui thread will be updating this value via the ParameterSlider objects etc.
    std::atomic<float> normalisedValue;
    
    float customValue = 0.0;
    float customMinValue = 0.0;
    float customMaxValue = 0.0;
    
    //Used with ParameterTypes enum to represent filter type, i.e lowpass, highpass etc.
    int parameterType;
    String name;
    
    std::function<void(float)> setValueCallback = nullptr;
};




#endif  // CustomAudioParameter_H_INCLUDED
