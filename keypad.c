/***********************************************
 *  Module:keypad
 *
 *  File Name:keypad.c
 *
 *  Description: keypad functions
 *
 *  Created on : 24/9/2019
 *
 *  Author: Ahmed Ekram&Ahmed Gaber
 ***********************************************/

#include "keypad.h"
//static uint8 keypad3x3(uint8 key);
#if (N_row==3) && (N_col==3)
					uint8 keypad3x3(uint8 value);
#elif (N_row==4) && (N_col==3)
					uint8 keypad4x3(uint8 value);
#elif (N_row==4) && (N_col==4)
					uint8 keypad4x4(uint8 value);
#endif
uint8 sampling_rate;
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
uint8 key_getpressed(void)
{
	uint8 row,col;
	static uint8 value=0;
	uint8 ret_value=0;
	static uint8 sampler=1;
	static uint8 temp_row=0;
	uint8 break_flag=0;
	static uint8 keypad_status=KEY_IDLE;
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
#if (N_row==3) && (N_col==3)
					value=keypad3x3((row*N_col)+col+1-6);
#elif (N_row==4) && (N_col==3)
					value=keypad4x3((row*N_col)+col+1);
#elif (N_row==4) && (N_col==4)
					value=keypad4x4((row*N_col)+col+1);
#endif
					keypad_status=KEY_PREPRESSED;
					temp_row=row;
					break_flag=1;
					ret_value=0;
					DIO_WritePin(PinB4,HIGH);
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
		keypad_status=KEY_PRESSED;
		ret_value=0;
		if(Get_Bit(KEYPAD_PORT_IN,temp_row)==0)
		{
			sampler++;
		}
		else
		{
			//sampler=1;
			keypad_status=KEY_NOTPRESSED;
		}

		if(sampler>=0)
		{
			sampler=1;
			keypad_status=KEY_PRESSED;
		}
		break;

	case KEY_PRESSED:

		ret_value=value;
		keypad_status=KEY_IDLE;
		break;
	case KEY_NOTPRESSED:
		ret_value=0;
		keypad_status=KEY_IDLE;
		break;
	}
	return ret_value;
}
#if (N_row==3) && (N_col==3)
uint8 keypad3x3(uint8 value)
{
	return value;
}
#elif (N_row==4) && (N_col==3)
uint8 keypad4x3(uint8 value)
{
	switch(value)
	{
	case 10:
		return '*'; // ASCII Code of *
			 break;
	case 11:
		return 0;
			 break;
	case 12:
		return '#'; // ASCII Code of #
			 break;
	default:
		return value;
		break;
}
}
#elif (N_row==4) && (N_col==4)
{
	switch(button_number)
		{
			case 1:
				return 7;
					break;
			case 2:
				return 8;
					break;
			case 3:
				return 9;
					break;
			case 4:
				return '%'; // ASCII Code of %
					break;
			case 5:
				return 4;
					break;
			case 6:
				return 5;
					break;
			case 7:
				return 6;
					break;
			case 8:
				return '*'; /* ASCII Code of '*' */
					break;
			case 9:
				return 1;
					break;
			case 10:
				return 2;
					break;
			case 11:
				return 3;
					break;
			case 12:
				return '-'; /* ASCII Code of '-' */
					break;
			case 13:
				return 13;  /* ASCII of Enter */
					break;
			case 14:
				return 0;
					break;
			case 15:
				return '='; /* ASCII Code of '=' */
					break;
			case 16:
				return '+'; /* ASCII Code of '+' */
					break;
			default:
				return value;
		}
	}
}
#endif
