/*
  ==============================================================================

    VAOnePoleFilter.h
    Created: 9 Jul 2015 8:20:19pm
    Author:  Joshua Marler

  ==============================================================================
*/

#ifndef VAONEPOLEFILTER_H_INCLUDED
#define VAONEPOLEFILTER_H_INCLUDED

#include "JuceHeader.h"
#include "AudioFilter.h"


/* 
   A very basic Virtual Analogue One Pole Filter based on calculations from The Art of VA Filter Design
   by Vadim Zavalishin see:

   NOTE : Need to implement oversampling as frequency response is incorrect at high frequencies approaching nyquist
   there is lost energy/gain which will be apparent on the filters response display (common issue with VA filters). You
   will notice the frequency response suddenly drops off as the cutoff approaches nyquist.
   This will be addressed in the next version.
 
*/

class VAOnePoleFilter : public AudioFilter
{

public:
    VAOnePoleFilter();
    
    virtual ~VAOnePoleFilter();
    
    // Must be called before playback starts to set sample rate etc.
    void initializeFilter(float initSampRate, float initMinFrequency, float initMaxFrequency) override;
    
    void setCutoff(float cutoff) override;
    
    //Overriding base class filter response functions for VA One Pole response
    float getMagnitudeResponse(float freq) const  override;
    float processFilter(float input, int channel) override;
    
private:
    // z1 delay element/state holder (performing analgue intergration equivalent)
    // set as a stereo option for now, possibly a better way of setting up / handling
    // stereo input between filter and plugin processor code but this is nice and simple.
    float z1 [2];
    
    // Big G value for billinear cutoff/pre-warping
    float G = 0.0;
};

#endif  // VAONEPOLEFILTER_H_INCLUDED