#ifndef STRETCHSENSEGLOVE_H
#define STRETCHSENSEGLOVE_H
#include <Arduino.h>
#include "SignalFilter.h"

class StretchSenseGlove
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
        StretchSenseGlove();
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