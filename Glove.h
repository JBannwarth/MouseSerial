// Glove.h

// Created: Jeremie Bannwarth, 04/12/2014 
// Last modified: Jeremie Bannwarth, 05/12/2014 

#ifndef GLOVE_H
#define GLOVE_H
#include <Arduino.h>
#include "SignalFilter.h"

class Glove
{
    private:
        int16_t enablePin;
        int16_t clickPin;
        int16_t fwdPin;
        int16_t bwdPin;
        int16_t calPin;
        int16_t potXPin;
        int16_t potYPin;

        bool enablePressed;
        bool clickPressed;
        bool fwdPressed;
        bool bwdPressed;
        bool calPressed;
    
        int16_t xRaw;
        int16_t yRaw;
        int16_t xFiltd;
        int16_t yFiltd;

        SignalFilter FilterX;
        SignalFilter FilterY;

    public:
        Glove();
        void begin(int16_t enablePinNew, 
                   int16_t clickPinNew,
                   int16_t fwdPinNew,
                   int16_t bwdPinNew,
                   int16_t calPinNew,
                   int16_t potXPin,
                   int16_t potYPin);
        void update();
        void transferFilteredData();
        void transferRawData();
};

#endif