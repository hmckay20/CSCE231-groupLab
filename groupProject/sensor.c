/**************************************************************************//**
 *
 * @file sensor.c
 *
 * @author Teighan Peterson, Erin Hughey, Hunter Mcay
 *
 * @brief Code to manage the distance sensor.
 *
 ******************************************************************************/

/*
 * RangeFinder GroupLab assignment and starter code (c) 2023 Christopher A. Bohn
 * RangeFinder solution (c) the above-named students
 */

#include <CowPi.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "sensor.h"
#include "shared_variables.h"

volatile SensorState sensorState = READY;
const int trigPin = 2;
const int echoPin = 3;
volatile unsigned long pulseStartTime = 0;
volatile unsigned long pulseEndTime = 0;
volatile bool objectDetected = false;
volatile long objectDistance = 0;

void initialize_sensor(void) {

pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << CS10) | (1 << CS11) | (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

void manage_sensor(void) {

  if(pingRequested){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    pingRequested = false;
  }
  if (objectDetected){
    long timeElapsed = pulseEndTime - pulseStartTime;
    objectDistance = timeElapsed * 0.034 / 2;
    objectDetected = false;
  }

}

ISR(TIMER1_OVF_vect){
  
if(sensorState == ACTIVE_LISTENING){
  
  objectDetected = false;
  objectDistance = 0;

  sensorState = QUIESCENT;

  TCNT1 = 0;
}
  
if (sensorState == ACTIVE_DETECTED){
  objectDetected = true;
  sensorState = QUIESCENT;
}
}

void echoPin_ISR(){
if(digitalRead(echoPin) == HIGH){
  pulseStartTime = micros();
}else{
  pulseEndTime = micros();
  objectDetected = true;
}
}
