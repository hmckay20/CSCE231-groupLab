/**************************************************************************//**
 *
 * @file alarm.c
 *
 * @author Teighan Peterson, Erin Hughey, Hunter Mcay
 * @author (STUDENTS -- TYPE YOUR NAMES HERE)
 *
 * @brief Code to manage the piezodisc and LEDs.
 *
 ******************************************************************************/

/*
 * RangeFinder GroupLab assignment and starter code (c) 2023 Christopher A. Bohn
 * RangeFinder solution (c) the above-named students
 */

#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "alarm.h"
#include "shared_variables.h"


const unsigned int on_period = 7000;    // 50ms ÷ 100μs //add code to illuminate both LEDs for the same 50ms that the piezodisc generates
                                        // a tone and then deluminates the LEDs just as the tone is silenced

volatile unsigned int total_period = 50000;

void initialize_alarm(void) 
{
    // pinMode(trigPin, OUTPUT);
    // pinMode(echoPin, INPUT);
    noInterrupts();
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    OCR2A = 156; // (adjust as needed)
    TCCR2A |= (1 << WGM21); // Set to ctc mode
    TCCR2B |= (1 << CS22) | (1 << CS21); // Set prescaler to 256
    TIMSK2 |= (1 << OCIE2A); // Enable compare match interrupt
    interrupts();
}

void manage_alarm(void) 
{
    if (millis() % total_period < on_period) 
    {
        activate_alarm();
    } 
    else 
    {
        deactivate_alarm();
    }
}


void activate_alarm(void) 
{
    //activate alarm 
}

void deactivate_alarm(void) 
{
    //deactivate alarm
}

ISR(TIMER2_COMPA_vect) 
{
    // In that ISR, add code so that on every other invocation will place a 1 on Arduino pin D13
    // and will place a 0 on the alternate invocations.
    // Test that your code is generating a tone on the piezodisc, and correct any errors.

    static bool toggle = false;

    if (toggle) 
    {
        digitalWrite(13, HIGH);
    } 
    else 
    {
        digitalWrite(13, LOW);
    }

    toggle = !toggle;
}
