// SerialMouse sketch
//
// Corresponding Processing file: Processing_2014_11_13
//
// Andreas Tairych
// DOOM game controller project
// Reads two potentiometers for two mouse axes
// Reads a button for left click
// Reads one button for forward movement
// Reads one button for backward movement
// Generates a string and sends it via serial port to be read by the above Processing file
// Reads a button for enabling calibration mode
// 5/11/2014
// Last modified: 04/12/2014, by Jeremie Bannwarth

// #define DEBUG

#include "StretchSenseGlove.h"

const int enablePin = 2; // Enable pin; LOW on digital pin enables mouse
const int clickPin  = 3; // Left click; LOW on digital pin activates left click
const int potXPin   = 5; // Analog pin for x-axis pot
const int potYPin   = 4; // Analog pin for y-axis pot

const int fwdPin   = 4; // Digital pin forward movement
const int bwdPin  = 5; // Digital pin backward movement

const int calPin    = 6; // Digital pin to enable sensor calibration

// StretchSenseGlove object keeps track of sensor measurements and
// handles data transfer
StretchSenseGlove StretchSenseGlove;

int transferCounter = 0; // Counter used to keep track of when to transfer data
const int transferThreshold = 4; // Transfer every 5th sample (20 Hz)

void setup()
{
    // Configuration of interrupts
    cli(); // Disable interrupts

    // Set timer1 interrupt at 100Hz
    TCCR1A = 0;
    TCCR1B = 0;
    // Initialize counter value to 0
    TCNT1  = 0;
    // Set compare match register for 1ms increments
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

    StretchSenseGlove.begin(enablePin, clickPin, fwdPin, bwdPin, calPin,
        potXPin, potYPin);

    sei(); // enable interrupts
} // void setup()

void loop()
{  
    // Idle
    __asm__("nop\n\t");
} // void loop()

ISR(TIMER1_COMPA_vect)
{
    sei();

    StretchSenseGlove.update();

    if (transferCounter >= transferThreshold)
    {
        StretchSenseGlove.transferData();
        transferCounter = 0;
    }
    else
    {
        transferCounter++;
    }
} // ISR(TIMER1_COMPA_vect)
