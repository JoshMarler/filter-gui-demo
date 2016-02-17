/*
  ==============================================================================

    AudioFilter.h
    Created: 25 Jul 2015 10:05:58am
    Author:  Joshua Marler

  ==============================================================================
*/

#ifndef AUDIOFILTER_H_INCLUDED
#define AUDIOFILTER_H_INCLUDED

#include "JuceHeader.h"

//Abstract audio filter base class
class AudioFilter
{
public:
    
    AudioFilter();
    
    virtual ~AudioFilter();
    
    //Filters deriving from this class must implement their process method
    virtual float processFilter (float input, int channel) = 0;
    
    /* 
        Filters deriving from this class must implement their own initialization code - i.e for flushing storage registers/state holders etc.
        Must be called before playback starts to set sample rate etc. 
     */
    virtual void initializeFilter (float initSampleRate, float initMinFrequency, float initMaxFrequency) = 0;
    
    inline void setSampleRate (float newSampRate) {sampleRate = newSampRate;}
    inline float getSampleRate() const {return sampleRate;}
    
    inline void setMinFrequency (float newMinFrequency) {minFrequency = newMinFrequency;}
    inline float getMinFrequency() const {return minFrequency;}
    
    inline void setMaxFrequency (float newMaxFrequency) {maxFrequency = newMaxFrequency;}
    inline float getMaxFrequency() const {return maxFrequency;}
    
   
    /* 
        Parameter set and get methods made virtual to facilitate use in different types of filters - i.e virtual analogue filters where
        cutoff frequencies may need to be pre-warped etc.
     */
    virtual void setCutoff (float newCutoff);
    virtual float getCutoff() const;
    virtual void setQFactor (float newQFactor);
    virtual float getQFactor() const;
    virtual void setGain (float newGain);
    virtual float getGain() const;
    
    /* 
        Filter response functions that can be overriden in baseclass to return the filters magnitude and phase response.
        These can be used to provide frequency response for displays and GUI components etc. Default implementations just return 0.0.
        These functions do not HAVE to be implemented - the filter object will run fine without them.
    */
    virtual float getMagnitudeResponse(float freq) const;
    virtual float getPhaseResponse(float freq) const;
    
    void setFilterType (int newFilterType);
    int getFilterType() const;
    
    //Filter types / response shapes - lowpass, highpass etc.
    enum filterTypeList
    {
        LowPass = 0,
        HighPass
    };
    
protected:
    
    float sampleRate = 0.0;
    float minFrequency = 0.0;
    float maxFrequency = 0.0;
    
    //Wrap these as std::atomic ? What if they are updated by lfo etc and the gui thread also reads them in some way through magnitudeResponse call etc.
    float cutoffFrequency = 0.0;
    float filterGain = 1.0;
    float qFactor = 0.0;
    
    int filterType = 0;
};

#endif  // AUDIOFILTER_H_INCLUDED
