/*
 * keypad.h
 *
 *  Created on: Sep 23, 2019
 *      Authors: Ahmed Ekram & Ahmed Gaber
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "keypad_Cfg.h"
/** Keypad status ***********/
/********Keypad Definitions*****/
#define KEY_IDLE 0
#define KEY_PREPRESSED 1
#define KEY_PRESSED 2
#define KEY_NOTPRESSED 3
/****Shared Variables***/
extern uint8 sampling_rate;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/**************************************************************************
 * Function Name : keypad_init
 *
 * Description	 : Initiating Keypad
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void keypad_init(void);
/**************************************************************************
 * Function Name : key_getpressed
 *
 * Description	 : Checking if we pressed on keypad
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : uint8 key button
 **************************************************************************/
extern uint8 key_getpressed(void);
#endif /* KEYPAD_H_ */
