// Glove.cpp

// Created: Jeremie Bannwarth, 04/12/2014 
// Last modified: Jeremie Bannwarth, 05/12/2014 

// #define DEBUG_GLOVE

#include "Glove.h"

// Constructor
Glove::Glove()
    : enablePin(0), clickPin(0), fwdPin(0), potXPin(0),
    potYPin(0), bwdPin(0), calPin(0), enablePressed(false),
    clickPressed(false), fwdPressed(false), bwdPressed(false),
    calPressed(false), xRaw(0), yRaw(0), xFiltd(0), yFiltd(0),
    FilterX(), FilterY()
{
    // Filters initialisation
    FilterX.begin();
    FilterX.setFilter('o');
    FilterX.setOrder(2);

    FilterY.begin();
    FilterY.setFilter('o');
    FilterY.setOrder(2);
} // Glove::Glove()

void Glove::begin(int16_t enablePinNew, int16_t clickPinNew,
    int16_t fwdPinNew, int16_t bwdPinNew, int16_t calPinNew,
    int16_t potXPinNew, int16_t potYPinNew)
{
    enablePin = enablePinNew;
    clickPin = clickPinNew;
    fwdPin = fwdPinNew;
    bwdPin = bwdPinNew;
    calPin = calPinNew;
    potXPin = potXPinNew;
    potYPin = potYPinNew;
} // void Glove::begin()

// Methods
void Glove::update()
{
    // Update analog inputs
    xRaw = ( 512 - analogRead(potXPin) ) / 2;
    xFiltd = FilterX.run(xRaw);
    yRaw = ( 512 - analogRead(potYPin) ) / 2 ;
    yFiltd = FilterY.run(yRaw);

    // Update digital inputs (and buffer them)
    // Note: digital inputs at switched to GND when a button
    // is pressed (ie. digitalRead(pin) = LOW)
    if ( !enablePressed && !digitalRead(enablePin) )
    {
        enablePressed = true;
    }

    if ( !clickPressed && !digitalRead(clickPin) )
    {
        clickPressed = true;
    }

    if ( !fwdPressed && !digitalRead(fwdPin) )
    {
        fwdPressed = true;
    }

    if ( !bwdPressed && !digitalRead(bwdPin) )
    {
        bwdPressed = true;
    }

    if ( !calPressed && !digitalRead(calPin) )
    {
        calPressed = true;
    } 
} // void Glove::update()

void Glove::transferFilteredData()
{
    // Send data in the format:
    // Data,x,y,enable,click,fwd,bwd,cal,
    Serial.print("Data,");
    Serial.print(xFiltd,DEC);
    Serial.print(",");
    Serial.print(yFiltd,DEC);
    Serial.print(",");

    #ifdef DEBUG_GLOVE
        Serial.print(xRaw,DEC);
        Serial.print(",");
        Serial.print(yRaw,DEC);
        Serial.print(",");
    #endif

    // Enable button
    Serial.print(enablePressed,DEC);
    Serial.print(",");

    // Left mouse button
    Serial.print(clickPressed,DEC);
    Serial.print(",");

    // Forward movement button
    Serial.print(fwdPressed,DEC);
    Serial.print(",");

    // Backward movement button
    Serial.print(bwdPressed,DEC);
    Serial.print(",");

    // Calibration button
    Serial.print(calPressed,DEC);

    // #ifdef DEBUG_GLOVE
    //     Serial.print(",");
    //     Serial.print(millis());
    // #endif

    Serial.println(",");

    // Reinitialise button buffers
    enablePressed = false;
    clickPressed  = false;
    fwdPressed    = false;
    bwdPressed    = false;
    calPressed    = false;
} // void Glove::transferData()

void Glove::transferRawData()
{
    // Send data in the format:
    // Data,x,y,enable,click,fwd,bwd,cal,
    Serial.print("Data,");
    Serial.print(xRaw,DEC);
    Serial.print(",");
    Serial.print(yRaw,DEC);
    Serial.print(",");

    // Enable button
    Serial.print(enablePressed,DEC);
    Serial.print(",");

    // Left mouse button
    Serial.print(clickPressed,DEC);
    Serial.print(",");

    // Forward movement button
    Serial.print(fwdPressed,DEC);
    Serial.print(",");

    // Backward movement button
    Serial.print(bwdPressed,DEC);
    Serial.print(",");

    // Calibration button
    Serial.print(calPressed,DEC);

    #ifdef DEBUG_GLOVE
        Serial.print(",");
        Serial.print(millis());
    #endif

    Serial.println(",");

    // Reinitialise button buffers
    enablePressed = false;
    clickPressed  = false;
    fwdPressed    = false;
    bwdPressed    = false;
    calPressed    = false;
} // void Glove::transferData()