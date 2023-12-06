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

int buttonState = 0;
int lastButtonState = 0; 
int currentButtonState = 0; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;; 
bool debounceRead(int pin){

   currentButtonState = digitalRead(pin);

  if(currentButtonState != lastButtonState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime ) > debounceDelay ){
    buttonState = currentButtonState;
  }
  lastButtonState = currentButtonState;
  return lastButtonState;
}
void initialize_controls(void) 
{

pinMode(switchPin1, INPUT);
pinMode(switchPin2, INPUT);
pinMode(pushButtonPin, INPUT);
pingRequested = false;

}

void manage_controls(void) 
{
  bool switch1State = debounceRead(11);
  bool switch2State = debounceRead(12);

  if (cowpi_left_button_is_pressed() && (currentMode == SINGLE_PULSE))
  {
    pingRequested = true;
  }

  if ((cowpi_left_switch_is_in_left_position()) && (cowpi_right_switch_is_in_left_position())) //left to left 
  {
      currentMode = NORMAL;
  } 
  else if ((cowpi_left_switch_is_in_right_position()) && (cowpi_right_switch_is_in_left_position())) //right left
  {
    currentMode = SINGLE_PULSE;


  } 
  else if ((cowpi_left_switch_is_in_right_position()) && (cowpi_right_switch_is_in_right_position())) //right right
  {
    currentMode = THRESHOLD_ADJUSTMENT;
  } 
  else if ((cowpi_left_switch_is_in_left_position()) && (cowpi_right_switch_is_in_right_position())) //left right  
  {
    currentMode = CONTINUOUS_TONE;
  }

}