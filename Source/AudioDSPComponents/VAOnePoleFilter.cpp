/*
  ==============================================================================

    VAOnePoleFilter.cpp
    Created: 9 Jul 2015 8:20:19pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "VAOnePoleFilter.h"


/*VAOnePoleFilterReponse method declerations*/

VAOnePoleFilterResponse::VAOnePoleFilterResponse(const AudioFilter& owningFilter)
: AudioFilterResponse(owningFilter)
{
    
}


VAOnePoleFilterResponse::~VAOnePoleFilterResponse()
{

}


float VAOnePoleFilterResponse::calculateMagnitudeReponse(float frequency) const
{
    float magnitude = 0.0;
    float T = 1/this->getSampleRate();
    float wd =  2 * M_PI * frequency;
    float sValue =  (2/T) * tan(wd*T/2);
    float cutOffValue = this->getCutoffFrequency();
    
    /* This is the digital transfer function which is equal to the analogue transfer function
    evaluated at H(s) where s = (2/T) * tan(wd*T/2).
    See Art Of VA Filter Design 3.8 Bilinear Transform Section */
    switch (this->getFilterType()) {
        case AudioFilter::filterTypeList::LowPass:
            //VA Lowpass Frequency response wc/s+wc
            magnitude = cutOffValue/(sValue + cutOffValue);
            break;
        case AudioFilter::filterTypeList::HighPass:
            //VA Highpass Frequency response s/s+wc
            magnitude = sValue/(sValue + cutOffValue);
            break;
        default:
            break;
    }
    
    magnitude = magnitude * this->getGain();
    
    //Convert to db for log db response display
    magnitude = Decibels::gainToDecibels(magnitude);
    
    return  magnitude;
}





/* VAOnePoleFilter method declerations */

VAOnePoleFilter::VAOnePoleFilter()
{
    //Initializing base class filter response member object ptr to VAOnePoleFilterResponse object
    filterResponse.reset(new VAOnePoleFilterResponse(*this));
}


VAOnePoleFilter::~VAOnePoleFilter()
{

}

//Set variables and flush state registers in initialization function. Must be called before playback starts
void VAOnePoleFilter::initializeFilter(float initSampleRate, float initMinFrequency, float initMaxFrequency)
{
    sampleRate = initSampleRate;
    minFrequency = initMinFrequency;
    maxFrequency = initMaxFrequency;
    
    //clear the delay elements/state holders
    z1[0] = 0.0;
    z1[1] = 0.0;
}


void VAOnePoleFilter::setCutoffFrequency(float newCutoff)
{
    cutoffFrequency = newCutoff;
    
    //Cutoff prewarping, billinear transform filters see art of va filter design.
    float wd = 2 * M_PI * cutoffFrequency;
    float T = 1/sampleRate;
    
    /* Desired analogue frequency / these are virtual analogue filters so this is the cutoff / frequency response we require for out filter algorithm */
    float wa = (2/T) * tan(wd*T/2);
    
    //Passing in pre-warped/analogue cutoff frequency to use in virtual analogue frequecny response calculations
    filterResponse->setCutoffFrequency(wa);
    
    float g = wa * T/2;
    G = g/(1.0 + g);
}


float VAOnePoleFilter::processFilter(float input, int channel)
{
    float v = (input - z1[channel]) * G;
    float lowpassOutput = v + z1[channel];
    
    //Update the z1 delay / state holder with new filter output for use in next sample
    z1 [channel]= lowpassOutput + v;
    
    float highpassOutput = input - lowpassOutput;
    
    if (this->filterType == LowPass)
    {
        return filterGain * lowpassOutput;
    }
    
    else if (this->filterType == HighPass)
    {
        return filterGain * highpassOutput;
    }
    
    else
    {
        //Unrecognised filter type/invalid argument passed to setFilterType()
        return 0.0;
    }
}






