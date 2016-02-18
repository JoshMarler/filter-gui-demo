/*
  ==============================================================================

    ParameterSlider.cpp
    Created: 17 Feb 2016 9:58:49pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "CustomSlider.h"

CustomSlider::CustomSlider (AudioProcessorParameter& p)
: Slider (p.getName (256)), param (p)
{
    setRange (0.0, 1.0, 0.0);
    startTimerHz (30);
    updateSliderPos();
}

void CustomSlider::valueChanged()
{
    param.setValue ((float) Slider::getValue());
}

void CustomSlider::timerCallback()
{
    updateSliderPos();
}

void CustomSlider::startedDragging()
{
    param.beginChangeGesture();
}
void CustomSlider::stoppedDragging()
{
    param.endChangeGesture();
}

double CustomSlider::getValueFromText (const String& text)
{
    return param.getValueForText (text);
}


String CustomSlider::getTextFromValue (double value)
{
    return param.getText ((float) value, 1024);
}

void CustomSlider::updateSliderPos()
{
    const float newValue = param.getValue();
    
    if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
        Slider::setValue (newValue);
}