/*
  ==============================================================================

    ParameterSlider.cpp
    Created: 17 Feb 2016 9:58:49pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "ParameterSlider.h"

ParameterSlider::ParameterSlider (AudioProcessorParameter& p)
: Slider (p.getName (256)), param (p)
{
    setRange (0.0, 1.0, 0.0);
    startTimerHz (30);
    updateSliderPos();
}

void ParameterSlider::valueChanged()
{
    param.setValue ((float) Slider::getValue());
}

void ParameterSlider::timerCallback()
{
    updateSliderPos();
}

void ParameterSlider::startedDragging()
{
    param.beginChangeGesture();
}
void ParameterSlider::stoppedDragging()
{
    param.endChangeGesture();
}

double ParameterSlider::getValueFromText (const String& text)
{
    return param.getValueForText (text);
}


String ParameterSlider::getTextFromValue (double value)
{
    return param.getText ((float) value, 1024);
}

void ParameterSlider::updateSliderPos()
{
    const float newValue = param.getValue();
    
    if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
        Slider::setValue (newValue);
}