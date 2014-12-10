// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

// SignalFilter - Library to Filter Sensor Data using digital filters
// Available filters: Chebyshev & Bessel low pass filter (1st & 2nd order)

// Modified by: Jérémie Bannwarth, 04/12/2014

#ifndef SignalFilter_h
#define SignalFilter_h
#include <Arduino.h>
#include "FilterCoefficients.h"

#define NUMBER_SAMPLES 16

class SignalFilter
{
    public:
        SignalFilter();
        void begin();

        void setFilter(uint8_t filter); // 'c' -> Chebyshev, 'b' -> Bessel, 'o' -> other (custom)
        void setOrder(int16_t order);    // Only 1 or 2
        void printSamples();

        int16_t run(int16_t data);

    private:
        int16_t run2ndOrderSection(int16_t data);
        int16_t runChebyshev(int16_t data);
        int16_t runBessel(int16_t data);
        int16_t runMedian(int16_t data);
        int16_t runRollingMean(int16_t data);
        uint8_t _filter;
        int16_t _order;
        int16_t _average;
        int16_t _median;
        int16_t _helper;
        int16_t _counter;

        int16_t _v[3];
        int16_t _vMean[NUMBER_SAMPLES];
        int16_t _indexMean;
        int16_t _sumMean;
};
#endif
