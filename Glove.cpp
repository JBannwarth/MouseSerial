// Glove.cpp

// Created: Jeremie Bannwarth, 04/12/2014 
// Last modified: Jeremie Bannwarth, 05/12/2014 

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
    FilterX.setFilter('b');
    FilterX.setOrder(1);

    FilterY.begin();
    FilterY.setFilter('b');
    FilterY.setOrder(1);
} // Glove::Glove()

void Glove::begin(int enablePinNew, int clickPinNew, int fwdPinNew,
     int bwdPinNew, int calPinNew, int potXPinNew, int potYPinNew)
{
    enablePin = enablePinNew;
    clickPin = clickPinNew;
    fwdPin = fwdPinNew;
    bwdPin = bwdPinNew;
    calPin = calPinNew;
    potXPin = potXPinNew;
    potYPin = potYPinNew;

    // Configuration of digital inputs
    // Pins are high by default, turn on pull-ups
    pinMode(enablePin, INPUT);
    digitalWrite(enablePin, HIGH);

    pinMode (clickPin, INPUT);
    digitalWrite(clickPin, HIGH);

    pinMode (fwdPin, INPUT);
    digitalWrite(fwdPin, HIGH);

    pinMode (bwdPin, INPUT);
    digitalWrite(bwdPin, HIGH);

    pinMode (calPin, INPUT);
    digitalWrite(calPin, HIGH);
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