/*
  ==============================================================================

    FilterResponseDisplay.h
    Created: 20 Jul 2015 3:22:56pm
    Author:  Joshua Marler

  ==============================================================================
*/

#ifndef FILTERRESPONSEDISPLAY_H_INCLUDED
#define FILTERRESPONSEDISPLAY_H_INCLUDED

#include "JuceHeader.h"
#include "AudioFilter.h"

// A filter magnitude response display class
// modified from and based on some code by semanticaudio
// see  https://github.com/semanticaudio/SAFE
// Check the SAFE FilterGraph class for reference.

class FilterResponseDisplay : public Component
{
public:
    FilterResponseDisplay(const AudioFilterResponse& filterResponse);
    ~FilterResponseDisplay();
    
    void paint(Graphics& g) override;
    
    //Filter response type drawing functions
    void drawLowpass();
    void drawHighpass();
    
    //Sets the colour of the filters response curve
    void setMagResponseColour(Colour newColour);
    
    void setDisplayBackgroundColour(Colour newColour);
    
    float xAxisToFrequency (float xPos);
    float dbToYAxis(float db);
    
    void setMaxDecibels(float maxDB);
    
private:
    //The AudioFilterResponse object the display will use to draw the magnitude response curve
    const AudioFilterResponse* filterResponseToUse;
    
    //Drawing / Graphics members
    Path magnitudeResponsePath;
    float filterPathThickness = 4.0;
    Colour magResponseColour;
    Colour displayBackgroundColor;
    
    float minFrequency = 0.0;
    float maxFrequency = 0.0;
    float maxDecibels = 0.0;
    
};

#endif  // FILTERRESPONSEDISPLAY_H_INCLUDED
