// MouseSerial.ino

// Corresponding Processing file: Processing_2014_11_13

// DOOM game controller project
// - Reads two potentiometers for two mouse axes
// - Reads a button for left click
// - Reads one button for forward movement
// - Reads one button for backward movement
// - Generates a string and sends it via serial port to be read  
//   by the above Processing file
// - Reads a button for enabling calibration mode

// Created: Andreas Tairych, 05/11/2014
// Last modified: Jeremie Bannwarth, 05/12/2014 

// #define DEBUG
// #define USE_RAW_DATA
// #define DEBUG_GLOVE

#include "Glove.h"

// Digital pins, activated when pulled LOW
const int16_t enablePin = 2; // Enable pin
const int16_t clickPin  = 3; // Left click
const int16_t fwdPin    = 4; // Forward movement
const int16_t bwdPin    = 5; // Backward movement
const int16_t calPin    = 6; // Enable sensor calibration

// Analog pins
const int16_t potYPin   = 4; // Y-axis pot
const int16_t potXPin   = 5; // X-axis pot

// Glove object keeps track of sensor measurements and
// handles data transfer
Glove Glove;

// Counter used to keep track of when to transfer data
int16_t transferCounter = 0; 
const int16_t transferThreshold = 4; // Transfer every 5th sample (20 Hz)

void setup()
{
    // -------------- Configuration of interrupts --------------
    cli(); // Disable interrupts

    // Set timer1 interrupt at 100Hz
    TCCR1A = 0;
    TCCR1B = 0;
    // Initialize counter value to 0
    TCNT1  = 0;
    // Set compare match register for 10ms increments
    OCR1A = 19999; // = (16*10^6) / (100*8) - 1
    // Turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS11 for 8 prescaler
    TCCR1B |= (1 << CS11);
    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // High baud rate is required to transfer all the required data 
    // within the allocated 10ms
    Serial.begin(57600);

    // --------------- Initialise pins and glove ---------------
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

    Glove.begin(enablePin, clickPin, fwdPin, bwdPin, calPin,
        potXPin, potYPin);

    sei(); // Enable interrupts
} // void setup()

void loop()
{  
    // Idle
    __asm__("nop\n\t");
} // void loop()

ISR(TIMER1_COMPA_vect)
{
    sei();

    Glove.update();

    if (transferCounter >= transferThreshold)
    {
        #ifdef USE_RAW_DATA
            Glove.transferRawData();
        #else
            Glove.transferFilteredData();
        #endif
        transferCounter = 0;
    }
    else
    {
        transferCounter++;
    }
} // ISR(TIMER1_COMPA_vect)
