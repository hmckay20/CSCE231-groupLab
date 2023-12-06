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

volatile cowpi_ioport_t *ioports;   // an array of I/O ports
volatile cowpi_i2c_t *i2c;   
void initialize_controls(void) 
{

    ioports = (cowpi_ioport_t *)(0x23);
    i2c = (cowpi_i2c_t *)(0xB8);
}
bool right_switch_is_in_right_position(void) {

   bool switch_in_position = (ioports[D8_D13].input & (1 << 2));
    return cowpi_debounce_byte(switch_in_position, RIGHT_SWITCH_RIGHT);
}
bool left_switch_is_in_right_position(void) { //DONE

    bool switch_in_position = (ioports[D8_D13].input & (1 << 3));
    return cowpi_debounce_byte(switch_in_position, LEFT_SWITCH_RIGHT);
}
bool left_switch_is_in_left_position(void) { //DONE
    return !left_switch_is_in_right_position();
}
bool right_switch_is_in_left_position(void) { //DONE
    return !right_switch_is_in_right_position();
}

void manage_controls(void) 
{
  if(right_switch_is_in_left_position() == true && left_switch_is_in_left_position() == true ){ 
currentMode = NORMAL;

}
  if(right_switch_is_in_left_position() == false && left_switch_is_in_left_position() == false ){ 
currentMode = THRESHOLD_ADJUSTMENT;

}
  if(right_switch_is_in_left_position() == false && left_switch_is_in_left_position() == true ){ 
currentMode = CONTINUOUS_TONE;

}
  if(right_switch_is_in_left_position() == false && left_switch_is_in_left_position() == true ){ 
currentMode = SINGLE_PULSE;


}
}

