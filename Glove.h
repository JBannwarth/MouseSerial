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
        int enablePin;
        int clickPin;
        int fwdPin;
        int bwdPin;
        int calPin;
        int potXPin;
        int potYPin;

        bool enablePressed;
        bool clickPressed;
        bool fwdPressed;
        bool bwdPressed;
        bool calPressed;
    
        int xRaw;
        int yRaw;
        int xFiltd;
        int yFiltd;

        SignalFilter FilterX;
        SignalFilter FilterY;

    public:
        Glove();
        void begin(int enablePinNew, 
                   int clickPinNew,
                   int fwdPinNew,
                   int bwdPinNew,
                   int calPinNew,
                   int potXPin,
                   int potYPin);
        void update();
        void transferData();
};

#endif