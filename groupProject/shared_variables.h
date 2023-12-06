/**************************************************************************//**
 *
 * @file shared_variables.h
 *
 * @author Teighan Peterson, Erin Hughey, Hunter Mcay
 *
 * @brief Types and variables that need to be shared among the .c files.
 *
 ******************************************************************************/

/*
 * RangeFinder GroupLab assignment and starter code (c) 2023 Christopher A. Bohn
 * RangeFinder solution (c) the above-named students
 */

#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

#ifdef __cplusplus
extern "C" {
#endif

/*** DO NOT PLACE ANY CODE ABOVE THIS LINE! ***/

/* IF YOU NEED TO DECLARE ANY ENUMS OR STRUCTS THAT
   ARE USED BY MORE THAN ONE .c FILE, PLACE THEM HERE */
typedef enum {
  NORMAL,
  SINGLE_PULSE,
  THRESHOLD_ADJUSTMENT,
  CONTINUOUS_TONE
}OperationMode;

typedef enum {
  READY,
  ACTIVE_LISTENING,
  ACTIVE_DETECTED,
  QUIESCENT
} SensorState;


/* IF YOU NEED TO CREATE ANY GLOBAL VARIABLES
   THAT MUST BE SHARED BETWEEN .c FILES, THEN:
    - DECLARE THEM IN *ONE AND ONLY ONE* .c FILE AS A volatile VARIABLE
      example:   volatile unsigned long foo;
    - DECLARE THEM HERE AS AN extern volatile VARIABLE
      example:   extern volatile unsigned long foo;
*/

extern FILE *display;

extern OperationMode currentMode;
extern bool pingRequested;
extern volatile long objectDistance; // The distance to the detected object
extern volatile long threshold_distance; // The threshold distance for triggering the alarm
volatile bool objectDetected;

/*** DO NOT PLACE ANY CODE BELOW THIS LINE! ***/

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SHARED_VARIABLES_H
