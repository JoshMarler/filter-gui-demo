/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 19 Sep 2014 7:23:32pm
    Author:  Joshua Marler

  ==============================================================================
*/

#ifndef CustomLookAndFeel_H_INCLUDED
#define CustomLookAndFeel_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class CustomLookAndFeel : public LookAndFeel_V3

{
public:
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;
};



#endif  // CustomLookAndFeel_H_INCLUDED
