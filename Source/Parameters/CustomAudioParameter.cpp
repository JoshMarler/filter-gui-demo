 /*
  ==============================================================================

    CustomAudioParameter.cpp
    Created: 19 Jun 2015 7:27:04pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "CustomAudioParameter.h"

CustomAudioParameter::CustomAudioParameter(const String& paramName, int initParameterType)
{
    name = paramName;
    parameterType = initParameterType;
}


CustomAudioParameter::CustomAudioParameter(const String& paramName, int initParameterType, std::function<void(float)> initSetValueCallback)

{
    name = paramName;
    parameterType = initParameterType;
    setValueCallback = initSetValueCallback;
}


CustomAudioParameter::~CustomAudioParameter()
{

}


float CustomAudioParameter::getValue() const
{
    return value;
}


void CustomAudioParameter::setValue (float newValue)
{
    value = newValue;
    
    //Sets customValue parameter for different parameter types
    switch (parameterType) {
        case Regular_Float_Param:
            customValue = value;
            break;
        case Volt_Octave_Param:
            customValue = calcValueVoltOctaveExp(customMinValue, customMaxValue, value);
        default:
            break;
    }
    
    //If we have a setValueCallback function call it with our customValue
    if (setValueCallback != nullptr)
    {
            setValueCallback(customValue);
    }
   
}


void CustomAudioParameter::setCustomMinValue(float newCustomMinValue)
{
    customMinValue = newCustomMinValue;
}


void CustomAudioParameter::setCustomMaxValue(float newCustomMaxValue)
{
    customMaxValue = newCustomMaxValue;
}


float CustomAudioParameter::calcValueVoltOctaveExp(float minFrequencyLimit, float maxFrequencyLimit, float paramValue)
{
    float octaves = log2(maxFrequencyLimit/minFrequencyLimit);
    if(minFrequencyLimit == 0)
        return paramValue;
    
    // exp control
    return minFrequencyLimit * pow(2, paramValue * octaves);
}

float CustomAudioParameter::getDefaultValue() const
{
    return defaultValue;
}


String CustomAudioParameter::getName(int maximumStringLength) const
{
    return name;
}


String CustomAudioParameter::getLabel() const
{
    String labelValue = "";
    
    switch (parameterType)
    {
        case Regular_Float_Param:
            labelValue = "";
            break;
        case Volt_Octave_Param:
            labelValue = "Hz";
            break;
            
        default:
            break;
    }
    
    return labelValue;
}


float CustomAudioParameter::getValueForText(const String& text) const
{
    return text.getFloatValue();
    
}


String CustomAudioParameter::getText(float value, int/*Maximum String Length - default value provided/optional*/) const
{
    return  getLabel();
}


