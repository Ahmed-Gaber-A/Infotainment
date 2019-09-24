/***********************************************
 *  Module:LCD
 *
 *  File Name:LCD.h
 *
 *  Description: LCD prototypes and definitions
 *
 *  Created on : 24/9/2019
 *
 *  Author: Ahmed Ekram & Ahmed Gaber
 ***********************************************/

#ifndef LCD_H_
#define LCD_H_

#include "LCD_cfg.h"
/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/**************************************************************************
 * Function Name : LCD_sendCommand
 *
 * Description	 : Sending command
 *
 * INPUTS		 : command
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_sendCommand(uint8 command);
/**************************************************************************
 * Function Name : LCD_displayCharacter
 *
 * Description	 : Sending character
 *
 * INPUTS		 : character
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_displayCharacter(uint8 data);
/**************************************************************************
 * Function Name : LCD_displayString
 *
 * Description	 : Sending string
 *
 * INPUTS		 : string
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_displayString(const char *Str);
/**************************************************************************
 * Function Name : LCD_init
 *
 * Description	 : Initialize the LCD associated pins
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_init(void);
/**************************************************************************
 * Function Name : LCD_clearScreen
 *
 * Description	 : void
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_clearScreen(void);
/**************************************************************************
 * Function Name : LCD_displayStringRowColumn
 *
 * Description	 : going to specific location and display string
 *
 * INPUTS		 : uint8 row,uint8 col,const char *Str
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
/**************************************************************************
 * Function Name : LCD_goToRowColumn
 *
 * Description	 : going to specific location
 *
 * INPUTS		 : uint8 row,uint8 col
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_goToRowColumn(uint8 row,uint8 col);
/**************************************************************************
 * Function Name : LCD_intgerToString
 *
 * Description	 : displaying integer number
 *
 * INPUTS		 : int data
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void LCD_intgerToString(int data);
void itoa(int data,char buff[],int decimal); /* 10 for decimal */
#endif /* LCD_H_ */
