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

void AudioFilter::setCutoffFrequency(float newCutoffFrequency)
{
    
    cutoffFrequency = newCutoffFrequency;
    
    //Sets the cutoff frequency of this filters FilterResponse object for use in response/magnitude response calculations.
    filterResponse->setCutoffFrequency(newCutoffFrequency);
}

void AudioFilter::setFilterGain(float newGain)
{
    filterGain = newGain;
    //Sets the gain of this filters FilterResponse object for use in response/magnitude response calculations.
    filterResponse->setGain(newGain);
}

void AudioFilter::setQFactor(float newQFactor)
{
    qFactor = newQFactor;
}

void AudioFilter::setFilterType(int type)
{
    filterType = type;
}

int AudioFilter::getCurrentFilterType() const
{
    return filterType;
}

float AudioFilter::getFilterCutoff() const
{
    return cutoffFrequency;
}

float AudioFilter::getFilterQFactor() const
{
    return qFactor;
}

float AudioFilter::getFilterGain() const
{
    return filterGain;
}

AudioFilterResponse& AudioFilter::getFilterResponse()
{
    return *filterResponse;
}

