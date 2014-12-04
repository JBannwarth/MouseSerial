// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

// SignalFilter - Library to Filter Sensor Data using digital filters
// Available filters: Chebyshev & Bessel low pass filter (1st & 2nd order)

// Modified by: Jérémie Bannwarth, 04/12/2014

#ifndef SignalFilter_h
#define SignalFilter_h
#include <Arduino.h>

class SignalFilter
{
    public:
        SignalFilter();
        void begin();

        void setFilter(char filter); // 'c' -> Chebyshev, 'b' -> Bessel
        void setOrder(int order);    // Only 1 or 2
        void printSamples();

        int run(int data);

    private:
        int runChebyshev(int data);
        int runBessel(int data);
        int runMedian(int data);
        int runGrowing(int data);
        int runGrowing2(int data);
        char _filter;
        int _order;
        int _average;
        int _median;
        int _helper;
        int _counter;

        int _v[3];
};
#endif
