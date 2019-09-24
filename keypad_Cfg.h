/*
 * keypad.h
 *
 *  Created on: Sep 23, 2019
 *     Authors: Ahmed Ekram & Ahmed Gaber
 */
#include "DIO_operations.h"
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

#define R0C0 1
#define R0C1 2
#define R0C2 3
#define R1C0 4
#define R1C1 5
#define R1C2 6
#define R2C0 7
#define R2C1 8
#define R2C2 9




#endif /* KEYPAD_CFG_H_ */
