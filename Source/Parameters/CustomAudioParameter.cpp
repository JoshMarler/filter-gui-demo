 /*
  ==============================================================================

    CustomAudioParameter.cpp
    Created: 19 Jun 2015 7:27:04pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "CustomAudioParameter.h"

CustomAudioParameter::CustomAudioParameter(String initParameterID, String initParameterName, bool initUseNormalizedForCallback) : AudioProcessorParameterWithID(initParameterID, initParameterName), normalisedValue(0.0), unnormalisedValue(0.0)
{
    name = initParameterName;
    useNormalizedForCallback = initUseNormalizedForCallback;
    range.start = 0.0;
    range.end = 1.0;
}


CustomAudioParameter::CustomAudioParameter(String initParameterID, String initParameterName, bool initUseNormalizedForCallback, std::function<void(float)> initSetValueCallback) : AudioProcessorParameterWithID(initParameterID, initParameterName), normalisedValue(0.0), unnormalisedValue(0.0)
{
    name = initParameterName;
    useNormalizedForCallback = initUseNormalizedForCallback;
    setValueCallback = initSetValueCallback;
    range.start = 0.0;
    range.end = 1.0;
}


CustomAudioParameter::~CustomAudioParameter()
{
   
}


float CustomAudioParameter::getValue() const
{
    return normalisedValue.load();
}


void CustomAudioParameter::setValue (float newValue)
{
    normalisedValue.store(newValue);
    unnormalisedValue.store(range.convertFrom0to1(newValue));
    
    if (setValueCallback != nullptr)
    {
        if (useNormalizedForCallback)
        {
            setValueCallback(normalisedValue.load());
        }
        else
        {
            setValueCallback(unnormalisedValue.load());
        }
    }
}

void CustomAudioParameter::setNormalisableRange(NormalisableRange<float> newRange)
{
    range = newRange;
}

void CustomAudioParameter::setNormalisableRange(float start, float end)
{
    range.start = start;
    range.end = end;
}

float CustomAudioParameter::getDefaultValue() const
{
    return defaultValue;
}


String CustomAudioParameter::getName(int maximumStringLength) const
{
    return name;
}

void CustomAudioParameter::setLabel(String newLabelText)
{
    labelText = newLabelText;
}

String CustomAudioParameter::getLabel() const
{
    return labelText;
}


float CustomAudioParameter::getValueForText(const String& text) const
{
    return range.convertFrom0to1(text.getFloatValue());
}


String CustomAudioParameter::getText(float value, int/*Maximum String Length - default value provided/optional*/) const
{
    String text = String(range.convertFrom0to1(value)) + getLabel();
    return text;
}


