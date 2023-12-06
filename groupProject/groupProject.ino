/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file RangeFinder.cpp
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for RangeFinder GroupLab.
 *
 ******************************************************************************/

/*
 * RangeFinder GroupLab (c) 2023 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <CowPi.h>
#include "alarm.h"
#include "sensor.h"
#include "user_controls.h"

FILE *display;


void setup() {
    display = cowpi_setup(9600,
                          cowpi_configure_lcd_character_display(),
                          cowpi_configure_i2c(cowpi_discover_i2c_address(SDA, SCL))
    );
    if (display == NULL) {
        int i2c_configuration_line = __LINE__ - 3;
        fprintf_P(stderr, PSTR("Display was not configured!\n ***"));
        int8_t i2c_address = cowpi_discover_i2c_address(SDA, SCL);
        if (i2c_address == 0) {
            fprintf_P(stderr, PSTR("No I2C device detected.\n"));
        } else if (i2c_address == -1) {
            fprintf_P(stderr, PSTR("Multiple I2C devices detected.\n"));
            fprintf_P(stderr, PSTR("Modify line %d to hard-code the correct I2C address.\n"), i2c_configuration_line);
        } else {
            fprintf_P(stderr, PSTR("This does not appear to be an I2C problem.\n"));
        }
        fprintf_P(stderr, PSTR("\nRe-assigning display module's output to the console"));
        fprintf_P(stderr, PSTR("so that you can work on other parts of the assignment.\n\n"));
        display = stdout;
    }
    pinMode(2, OUTPUT);     // for the distance sensor's TRIG pin
    pinMode(3, INPUT);      // for the distance sensor's ECHO pin
    pinMode(13, OUTPUT);    // D13 should already be an output pin, but better safe than sorry
    initialize_controls();
    initialize_sensor();
    initialize_alarm();
}

void loop() {

    manage_controls();
    manage_sensor();
    manage_alarm();
}
