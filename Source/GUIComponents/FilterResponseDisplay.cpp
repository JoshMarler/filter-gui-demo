/*
  ==============================================================================

    FilterResponseDisplay.cpp
    Created: 20 Jul 2015 3:22:56pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "FilterResponseDisplay.h"


FilterResponseDisplay::FilterResponseDisplay(const AudioFilterResponse& filterReponse)
{
    filterResponseToUse = &filterReponse;
    
    minFrequency = filterResponseToUse->getMinFrequency();
    maxFrequency = filterResponseToUse->getMaxFrequency();
    
    /* Sets the filter response displays min - max decibel range - Try changing this value to lower or higher decibel ranges 
       to see the effect on the frequency response that is shown. If implementing a filter with resonant peaks you will need 
       to ensure the peak values do not exceed the maxDecibels level */
    maxDecibels = 20.00;
}


FilterResponseDisplay::~FilterResponseDisplay()
{

}


void FilterResponseDisplay::paint(Graphics& g)
{
    float width = (float)  getWidth();
    float height = (float) getHeight();
    
    float freq = 0.0;
    float magnitudeDBValue = 0.0;
    
    float filterPathThickness = 4.0;
    
    g.setColour(displayBackgroundColor);
    g.fillRect(0.0, 0.0, width, height);
    
    magnitudeResponsePath.clear();
    
    //Because we are closing the drawn path the start points for highpass and lowpass responses need to be at opposite ends of the component.
    int filterType = filterResponseToUse->getFilterType();
    
    if (filterType == AudioFilter::filterTypeList::LowPass)
    {
        /* If LowPass start path on left hand side of component i.e at 0.0f - using 0.0f - (filterPathThickness/2) for asthetic purposes
           Try commeting out - (filterPathThickness/2) to see the effect. This line hides the highlighted path edge so that the path edge/highlight 
           shows only on the top of the magnitude response path. */
        magnitudeResponsePath.startNewSubPath((0.0f - (filterPathThickness/2)), (getBottom() - (filterPathThickness/2)));
        magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(minFrequency);
        magnitudeResponsePath.lineTo((0.0f - (filterPathThickness/2)) , dbToYAxis(magnitudeDBValue));
        
        for (float xPos = 0.0; xPos < (width + (filterPathThickness/2)); xPos += (filterPathThickness/2))
        {
            //Get the frequency value for the filter's magnitude response calculation
            freq = xAxisToFrequency(xPos);
            magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(freq);
            magnitudeResponsePath.lineTo(xPos, dbToYAxis(magnitudeDBValue));
        }
        
        magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(maxFrequency);
        magnitudeResponsePath.lineTo((width + (filterPathThickness/2)), dbToYAxis(magnitudeDBValue));
        
        /* Dirty Trick to close the path nicely when cutoff is at max level (this is not apparent for virtual analogue filters that have not been
           oversampled when cutoff is close to nyquist as the response is pulled to zero). Try commenting this line out and running the plugin at 
           higher sample rate i.e 96khz to see the visual result of the path closing without this. */
        magnitudeResponsePath.lineTo((width + (filterPathThickness/2)), (getBottom() - (filterPathThickness/2)));
    }
    
    else if (filterType == AudioFilter::filterTypeList::HighPass)
    {
        //If HighPass start path on right hand side of component i.e at component width.
        magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(maxFrequency);
        magnitudeResponsePath.startNewSubPath((width + (filterPathThickness/2)), (getBottom() - (filterPathThickness/2)));
        magnitudeResponsePath.lineTo((width + (filterPathThickness/2)), dbToYAxis(magnitudeDBValue));
        
        for (float xPos = (width); xPos > (filterPathThickness/2); xPos -= (filterPathThickness/2))
        {
            //Get the frequency value for the filter's magnitude response calculation
            freq = xAxisToFrequency(xPos);
            magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(freq);
            magnitudeResponsePath.lineTo(xPos, dbToYAxis(magnitudeDBValue));
        }
        
        magnitudeDBValue = filterResponseToUse->calculateMagnitudeReponse(minFrequency);
        magnitudeResponsePath.lineTo ((0.0f - (filterPathThickness/2)), dbToYAxis(magnitudeDBValue));
        
        /* Dirty trick again to close the path nicely when cutoff at min level for High Pass - try cmmenting this line out to se the visual
           effect on the reponse path closing without it*/
        magnitudeResponsePath.lineTo ((0.0f - (filterPathThickness/2)), (getBottom() - (filterPathThickness/2)));
    }
    
    //Close the response path drawn
    magnitudeResponsePath.closeSubPath();
    
    g.setColour(magResponseColour);
    g.strokePath(magnitudeResponsePath, PathStrokeType(filterPathThickness));
    
    /* Fill area under/inside path with same colour at a lower alpha / highlight value.
       Try setting magResponseColout.withAlpha value to different values using JUCE_LIVE_CONSTANT to get a fill shade of your liking.
       i.e the following:  g.setColour(magResponseColour.withAlpha(JUCE_LIVE_CONSTANT((uint8) 0x9a))); then play with setting at runtime */
    g.setColour(magResponseColour.withAlpha((uint8) 0x9a));
    g.fillPath(magnitudeResponsePath);
    
}


void FilterResponseDisplay::setMagResponseColour(Colour newColour)
{
    magResponseColour = newColour;
}


void FilterResponseDisplay::setDisplayBackgroundColour(Colour newColour)
{
    displayBackgroundColor = newColour;
}

//Converts position along the FilterReponseDisplay component's X-Axis into frequency for use in filter response calculation.
float FilterResponseDisplay::xAxisToFrequency(float xPos)
{
    float width = getWidth();
    
    //Computes frequency from position on x axis of component. So if the xPos is equal to the component width the value returned will be maxFrequency.
    float frequency = minFrequency * pow((maxFrequency / minFrequency), (xPos / width));
    
    return frequency;
}


float FilterResponseDisplay::dbToYAxis(float dbGain)
{
    float height = getHeight();
    
    //Scale gain with this value, height of component is divded by maxDB * 2 for -max to +max db response display
    float scale = - (height) / (maxDecibels * 2);
    float scaledDbGain = dbGain * scale;
    
    /* Negative db values will result in a negative yposition so add height/2 to result to scale into
       correct component position for drawing. Test these calculations with a dbGain value equal to maxDecibels and
       yPostion computed will be equal to the filterResponseDisplay's height as is correct. */
    float yPosition = scaledDbGain + (height / 2);
    
    return yPosition;
}


void FilterResponseDisplay::setMaxDecibels(float maxDB)
{
    maxDecibels = maxDB;
}
