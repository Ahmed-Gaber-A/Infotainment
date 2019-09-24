/*
 * LCD_cfg.h
 *
 *  Created on: Sep 24, 2019
 *      Authors: Ahmed Ekram & Ahmed Gaber
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#include "standard_types.h"
#include "function_macros.h"
#include "Memory_map.h"
#include <util/delay.h>
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD HW Pins */
#define RS PinA1
#define RW PinA2
#define E  PinA3
#define LCD_CTRL_PORT PORTA
#define LCD_CTRL_PORT_DIR DDRA

#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA


#endif /* LCD_CFG_H_ */
