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
    called whenever parameter value changes. This class uses a NormalisableRange range object which defaults to 0.0 - 1.0 range unless
    otherwise specified using the setNormalisableRange function. 
 
    The value passed into setValue should still be between 0.0 and 1.0 - the NormalisableRange object is NOT used to convert values outside
    of a 0.0 - 1.0 range passed to setValue. The NormalisableRange converts 0.0 - 1.0 values to a custom range specified by the user which 
    can then be used for display purposes and also passed to the setValueCallback function. 
 */
class CustomAudioParameter : public AudioProcessorParameterWithID
{
public:
    
    CustomAudioParameter(String initParameterID, String initParameterName, bool initUseNormalizedForCallback);
    
    //initSetValueCallback is a callback function you can specify (using a lambda etc) that will be called every time the parameter value changes.
    CustomAudioParameter(String initParameterID, String initParameterName, bool initUseNormalizedForCallback, std::function<void(float)> initSetValueCallback);
    
    ~CustomAudioParameter();
    
    float getValue() const override;
    void setValue(float newValue) override;
    
    void setNormalisableRange(NormalisableRange<float> newRange);
    void setNormalisableRange(float start, float end);
    
    float getDefaultValue() const override;
    String getName(int maximumStringLength) const override;
    
    void setLabel(String newLabelText);
    String getLabel() const override;
    
    float getValueForText (const String& text) const override;
    String getText(float value, int = 0 /*Maximum String Length - default value provided/optional*/) const override;
    
private:
    
    float defaultValue = 0.5;
    NormalisableRange<float> range;
    
    //Using std::atomic for the host/GUI changeable value to stop any data race conditions etc. As per Timur's talk.
    //The gui thread will be updating this value via the ParameterSlider objects etc.
    std::atomic<float> normalisedValue;
    std::atomic<float> unnormalisedValue;
    
    bool useNormalizedForCallback;
    
    String name;
    String labelText = "";
    
    std::function<void(float)> setValueCallback = nullptr;
};




#endif  // CustomAudioParameter_H_INCLUDED
