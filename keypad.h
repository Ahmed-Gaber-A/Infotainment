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

#define KEY_IDLE 0
#define KEY_PREPRESSED 1
#define KEY_PRESSED 2
#define KEY_NOTPRESSED 3

extern uint8 Sampling_Rate ;
void keypad_init(void);
extern uint8 key_getpressed(void);
#endif /* KEYPAD_H_ */
