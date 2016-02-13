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


//Forward decleration of AudioFilterReponse class for use in AudioFilter.
class AudioFilterResponse;


//Abstract audio filter base class
class AudioFilter
{
public:
    
    AudioFilter();
    
    virtual ~AudioFilter();
    
    //Filters deriving from this class must implement their process method
    virtual float processFilter(float input, int channel) = 0;
    
    /* Filters deriving from this class must implement their own initialization code - i.e for flushing storage registers/state holders etc.
       Must be called before playback starts to set sample rate etc. */
    virtual void initializeFilter(float initSampleRate, float initMinFrequency, float initMaxFrequency) = 0;
    
    inline void setSampleRate(float newSampRate) {sampleRate = newSampRate;}
    inline float getSampleRate() const{return sampleRate;}
    
    inline void setMinFrequency(float newMinFrequency) {minFrequency = newMinFrequency;}
    inline float getMinFrequency() const {return minFrequency;}
    
    inline void setMaxFrequency(float newMaxFrequency) {maxFrequency = newMaxFrequency;}
    inline float getMaxFrequency() const {return maxFrequency;}
    
   
    /* Parameter set and get methods made virtual to facilitate use in different types of filters - i.e virtual analogue filters where
       cutoff frequencies may need to be pre-warped etc. */
    virtual void setCutoffFrequency(float newCutoff);
    virtual float getFilterCutoff() const;
    virtual void setQFactor(float newQFactor);
    virtual float getFilterQFactor() const;
    virtual void setFilterGain(float newGain);
    virtual float getFilterGain() const;
    
    
    void setFilterType(int newFilterType);
    int getCurrentFilterType() const;
    
    AudioFilterResponse& getFilterResponse();
    
    enum filterTypeList
    {
        LowPass = 0,
        HighPass
    };
    
protected:
    //This pointer should be initialised in the derived filter class by calling filterResponse.reset(new DerivedFilterClass());
    std::shared_ptr<AudioFilterResponse> filterResponse;
    
    float sampleRate = 0.0;
    float minFrequency = 0.0;
    float maxFrequency = 0.0;
    
    float cutoffFrequency = 0.0;
    float filterGain = 1.0;
    float qFactor = 0.0;
    
    
    int filterType = 0;
    
};


//The frequency response of the AudioFilter object
class AudioFilterResponse
{
public:
    
    AudioFilterResponse(const AudioFilter& initOwningAudioFilter);
    virtual ~AudioFilterResponse();
    
    virtual float calculateMagnitudeReponse(float frequency) const = 0;
    
    //Call this function from inside the owning AudioFilter object's setCutoffFrequency function so that the response is updated in sync.
    inline void setCutoffFrequency(float newCutoffFrequency) {cutOffFrequency = newCutoffFrequency;}
    
    //Call this function from inside the owning AudioFilter object's setFilterGain so that the response is updated in sync.
    inline void setGain(float newGain) {gain = newGain;}
    
    inline float getCutoffFrequency() const {return cutOffFrequency;}
    inline float getGain() const {return gain;}
    
    //Functions declared inline and use owningAudioFilter properties to synch with changes in the filter that this filter response object represents.
    inline float getMinFrequency() const {return owningAudioFilter->getMinFrequency();}
    inline float getMaxFrequency() const {return owningAudioFilter->getMaxFrequency();}
    inline float getSampleRate() const {return owningAudioFilter->getSampleRate();}
    
    inline int getFilterType() const {return owningAudioFilter->getCurrentFilterType();}
    
protected:
    
    
    
private:
    
    float cutOffFrequency = 0.0;
    float gain = 0.0;
    
    const AudioFilter* owningAudioFilter;
};



#endif  // AUDIOFILTER_H_INCLUDED
