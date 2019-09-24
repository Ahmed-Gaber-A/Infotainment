/*
 * keypad.c
 *
 *  Created on: Sep 23, 2019
 *      Authors: Ahmed Ekram & Ahmed Gaber
 */

#include "keypad.h"
//static uint8 keypad3x3(uint8 key);
uint8 keypad_status=KEY_IDLE;
void keypad_init(void)
{
	DIO_SetPinDirection(PinC2,INPUT);
	DIO_SetPinDirection(PinC3,INPUT);
	DIO_SetPinDirection(PinC4,INPUT);

	DIO_WritePin(PinC2,HIGH);
	DIO_WritePin(PinC3,HIGH);
	DIO_WritePin(PinC4,HIGH);

	DIO_SetPinDirection(PinC5,OUTPUT);
	DIO_SetPinDirection(PinC6,OUTPUT);
	DIO_SetPinDirection(PinC7,OUTPUT);
}

uint8 key_getpressed(void)
{
	uint8 row,col;
	static uint8 value=0;
	uint8 ret_value=0;
	static uint8 sampler=0;
	static uint8 temp_row=0;
	uint8 break_flag=0;
	DIO_SetPinDirection(PinB4,OUTPUT);
		switch(keypad_status)
		{
		case KEY_IDLE:
		for(col=0;col<N_col;col++)
		{
			KEYPAD_PORT_DIR=(0b00100000<<col);
			KEYPAD_PORT_OUT=(~(0b00100000<<col));
			for(row=2;row<N_row+2;row++)
			{
				if(Get_Bit(KEYPAD_PORT_IN,row)==0)
				{
					//Toggle_Bit(PORTB,(PinB4-8));
					value=(row*N_col)+col+1-6;
					keypad_status=KEY_PREPRESSED;
					temp_row=row;
					break_flag=1;
					break;
					
				}
			}
			if(break_flag==1)
			{
				break_flag=0;
				break;
			}
		}	
		
			break;
			case KEY_PREPRESSED:
			if(Get_Bit(KEYPAD_PORT_IN,temp_row)==0)
			{
				sampler++;
			}
			else
			{
				sampler=0;
				keypad_status=KEY_NOTPRESSED;
			}
			
			if(sampler==10)
			{
				sampler=0;
				keypad_status=KEY_PRESSED;
			}
			break;
			
			case KEY_PRESSED:
			     keypad_status=KEY_IDLE;
				ret_value=value;
			break;
			
			case KEY_NOTPRESSED:
			     ret_value=0;
			     keypad_status=KEY_IDLE;
			break;
		}
		return ret_value;
}
