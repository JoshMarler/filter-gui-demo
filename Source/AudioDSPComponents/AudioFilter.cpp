/*
  ==============================================================================

    AudioFilter.cpp
    Created: 25 Jul 2015 10:05:58am
    Author:  Joshua Marler

  ==============================================================================
*/

#include "AudioFilter.h"

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
}


float AudioFilter::getCutoff() const
{
    return cutoffFrequency;
}

void AudioFilter::setGain(float newGain)
{
    filterGain = newGain;
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

int AudioFilter::getFilterType() const
{
    return filterType;
}

//Default filter response implementations
float AudioFilter::getMagnitudeResponse(float freq) const
{
    return 0.0;
}

float AudioFilter::getPhaseResponse(float freq) const
{
    return 0.0;
}
