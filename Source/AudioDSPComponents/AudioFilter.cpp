/*
  ==============================================================================

    AudioFilter.cpp
    Created: 25 Jul 2015 10:05:58am
    Author:  Joshua Marler

  ==============================================================================
*/

#include "AudioFilter.h"


/*AudioFilterResponse Method Declerations*/

AudioFilterResponse::AudioFilterResponse(const AudioFilter& initOwningAudioFilter)
{
    owningAudioFilter = &initOwningAudioFilter;
}

AudioFilterResponse::~AudioFilterResponse()
{

}


/*AudioFilter Method Declerations*/
AudioFilter::AudioFilter()
{
    filterType = LowPass;
}

AudioFilter::~AudioFilter()
{

}

void AudioFilter::setCutoff(float newCutoffFrequency)
{
    
    cutoffFrequency = newCutoffFrequency;
    
    //Sets the cutoff frequency of this filters FilterResponse object for use in response/magnitude response calculations.
    filterResponse->setCutoffFrequency(newCutoffFrequency);
}


float AudioFilter::getCutoff() const
{
    return cutoffFrequency;
}

void AudioFilter::setGain(float newGain)
{
    filterGain = newGain;
    //Sets the gain of this filters FilterResponse object for use in response/magnitude response calculations.
    filterResponse->setGain(newGain);
}

float AudioFilter::getGain() const
{
    return filterGain;
}

void AudioFilter::setQFactor(float newQFactor)
{
    qFactor = newQFactor;
}

float AudioFilter::getQFactor() const
{
    return qFactor;
}

void AudioFilter::setFilterType(int type)
{
    filterType = type;
}

int AudioFilter::getCurrentFilterType() const
{
    return filterType;
}

AudioFilterResponse& AudioFilter::getFilterResponse()
{
    return *filterResponse;
}

