/*
  ==============================================================================

    VAOnePoleFilter.cpp
    Created: 9 Jul 2015 8:20:19pm
    Author:  Joshua Marler

  ==============================================================================
*/

#include "VAOnePoleFilter.h"

VAOnePoleFilter::VAOnePoleFilter()
{
    
}

VAOnePoleFilter::~VAOnePoleFilter()
{

}

//Set variables and flush state registers in initialization function. Must be called before playback starts
void VAOnePoleFilter::initializeFilter(float initSampleRate, float initMinFrequency, float initMaxFrequency)
{
    this->sampleRate = initSampleRate;
    this->minFrequency = initMinFrequency;
    this->maxFrequency = initMaxFrequency;
    
    //clear the delay elements/state holders
    z1[0] = 0.0;
    z1[1] = 0.0;
}


void VAOnePoleFilter::setCutoff(float newCutoff)
{
    this->cutoffFrequency = newCutoff;
    
    //Cutoff prewarping, billinear transform filters - see Art Of VA Filter Design.
    float wd = 2 * M_PI * this->cutoffFrequency;
    float T = 1/this->sampleRate;
    
    /* Desired analogue frequency / these are virtual analogue filters so this is the cutoff / frequency response we require for out filter algorithm */
    float wa = (2/T) * tan(wd*T/2);
    float g = wa * T/2;
    G = g/(1.0 + g);
}


float VAOnePoleFilter::processFilter(float input, int channel)
{
    float output = 0.0;
    float v = (input - z1[channel]) * G;
    float lowpassOutput = v + z1[channel];
    
    //Update the z1 delay / state holder with new filter output for use in next sample
    z1 [channel]= lowpassOutput + v;
    
    float highpassOutput = input - lowpassOutput;
    
    switch (this->filterType) {
            case AudioFilter::filterTypeList::LowPass:
                output = this->filterGain * lowpassOutput;
            break;
        case AudioFilter::filterTypeList::HighPass:
            output = this->filterGain * highpassOutput;
            break;
        default:
            break;
    }
    
    return output;
}

float VAOnePoleFilter::getMagnitudeResponse(float frequency) const
{
    float magnitude = 0.0;
    float T = 1/this->sampleRate;
    
    float wdCutoff = 2 * M_PI * this->cutoffFrequency;
    
    //Calculating pre-warped/analogue cutoff frequency to use in virtual analogue frequeny response calculations
    float cutOff = (2/T) * tan(wdCutoff*T/2);
    
    //Digital frequency to evaluate
    float wdEval =  2 * M_PI * frequency;
    float sValue =  (2/T) * tan(wdEval*T/2);
    
    
    /* This is the digital transfer function which is equal to the analogue transfer function
     evaluated at H(s) where s = (2/T) * tan(wd*T/2) hence why the cutoff used is the pre warped analogue equivalent.
     See Art Of VA Filter Design 3.8 Bilinear Transform Section */
    switch (this->filterType) {
        case AudioFilter::filterTypeList::LowPass:
            //VA Lowpass Frequency response wc/s+wc
            magnitude = cutOff/(sValue + cutOff);
            break;
        case AudioFilter::filterTypeList::HighPass:
            //VA Highpass Frequency response s/s+wc
            magnitude = sValue/(sValue + cutOff);
            break;
        default:
            break;
    }
    
    magnitude = magnitude * this->filterGain;
    
    //Convert to db for log db response display
    magnitude = Decibels::gainToDecibels(magnitude);
    return  magnitude;
}






