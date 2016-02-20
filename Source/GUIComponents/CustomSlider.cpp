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
    startTimerHz (30);
    updateSliderPos();
    
    range.start = 0.0;
    range.end = 1.0;
}

void CustomSlider::setRange(double min, double max)
{
    range.start = min;
    range.end = max;
    Slider::setRange(min, max);
}

void CustomSlider::setRange(double min, double max, double step)
{
    range.start = min;
    range.end = max;
    Slider::setRange(min, max, step);
}

void CustomSlider::valueChanged()
{
    float value = range.convertTo0to1((float) Slider::getValue());
    param.setValueNotifyingHost(value);
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
    return param.getText ((float) range.convertTo0to1(value), 1024);
}

void CustomSlider::updateSliderPos()
{
    float newValue = range.convertFrom0to1(param.getValue());
    
    if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
        Slider::setValue (newValue);
}