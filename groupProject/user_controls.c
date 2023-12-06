/**************************************************************************//**
 *
 * @file user_controls.c
 *
 * @author Teighan Peterson, Erin Hughey, Hunter Mcay
 *
 * @brief Code to get inputs from the user.
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
#include <string.h>
#include <stdlib.h>
#include "user_controls.h"
#include "shared_variables.h"
const int switchPin1 = 10;
const int switchPin2 = 11;
OperationMode currentMode = NORMAL;
bool pingRequested = false;
const int pushButtonPin = 9;


void initialize_controls(void) 
{

pinMode(switchPin1, INPUT);
pinMode(switchPin2, INPUT);
pinMode(pushButtonPin, INPUT);
pingRequested = false;
}

void manage_controls(void) 
{
  bool switch1State = digitalRead(switchPin1);
  bool switch2State = digitalRead(switchPin2);

  if (switch1State == LOW && switch2State == LOW) 
  {
    currentMode = NORMAL;
  } 
  else if (switch1State == HIGH && switch2State == LOW) 
  {
    currentMode = SINGLE_PULSE;
  } 
  else if (switch1State == HIGH && switch2State == HIGH) 
  {
    currentMode = THRESHOLD_ADJUSTMENT;
  } 
  else if (switch1State == LOW && switch2State == HIGH) 
  {
    currentMode = CONTINUOUS_TONE;
  }

  if (currentMode == SINGLE_PULSE && digitalRead(pushButtonPin) == HIGH)
  {
      pingRequested = true;
  }
}
