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
volatile long threshold_distance = 400;

const unsigned int on_period = 500;    // 50ms ÷ 100μs //add code to illuminate both LEDs for the same 50ms that the piezodisc generates
                                        // a tone and then deluminates the LEDs just as the tone is silenced

volatile unsigned int total_period = 500;
int counter = 0;
volatile bool alarmActive = false; 
void initialize_alarm(void) 
{
  pinMode(13, OUTPUT);
   // bool alarm_requested = false;

    noInterrupts();
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    OCR2A = 24; // (adjust as needed)
    TCCR2A |= (1 << WGM21); // Set to ctc mode
    TCCR2B |= (1 << CS22) | (1 << CS21); // Set prescaler to 256
    TIMSK2 |= (1 << OCIE2A); // Enable compare match interrupt
    interrupts();

}

void manage_alarm(void) 
{

    switch(currentMode) {
     case NORMAL: 
      break;
     
     
     case SINGLE_PULSE:
   
        if (objectDetected && objectDistance < threshold_distance) {
        //  printf("case one\n");
               alarmActive = true;
               counter = 0;
               //pingRequested = false;
               objectDetected = false;
      } else if( objectDetected && objectDistance > threshold_distance){
              alarmActive = false;
              counter = 0; 
              objectDetected = false;
              digitalWrite(12, HIGH);
              delay(500);
      }

      if (counter >= on_period) {
                alarmActive = false;
                digitalWrite(12, LOW);
             
            }
      break;

      case THRESHOLD_ADJUSTMENT:
          alarmActive = false;
      break;

      case CONTINUOUS_TONE:
          alarmActive = true;
   
      break;

    }
   
}


ISR(TIMER2_COMPA_vect) 
{
    // In that ISR, add code so that on every other invocation will place a 1 on Arduino pin D13
    // and will place a 0 on the alternate invocations.
    // Test that your code is generating a tone on the piezodisc, and correct any errors.

    static bool toggle = false;

if(alarmActive){
 // printf("alarm active\n");
    if (toggle) 
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
    } 
    else 
    {
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
    }
    toggle = !toggle;

} else{
  
  digitalWrite(13, LOW);

}
counter++;
//printf("%d", counter);
}
