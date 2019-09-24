/***********************************************
 *  Module:Infotainment
 *
 *  File Name:Infontainement.c
 *
 *  Description: Infotainment tasks
 *
 *  Created on : 24/9/2019
 *
 *  Author: Ahmed Ekram & Ahmed Gaber
 ***********************************************/

/************************************************************************/
/*				Include Libraries                                       */
/************************************************************************/
#include "infotainment.h"

/************************************************************************/
/*                    Global Variables                                   */
/************************************************************************/
uint8 Infotainment_Status = INFOTAINMENT_IDLE;
/************************************************************************/
/*		Shared Variables   (between Tasks)                              */
/************************************************************************/
static uint8 Infotainment_NewDataFlag_g=0 ;
static uint8 Infotainment_Result_g =0;
static uint8 Infotainment_Question_Index_g=0 ;
static uint8 Infotainment_Score = 0;

/************************************************************************/
/*   Questions Array of strings					   					  */
/************************************************************************/
const char *Infotainment_Questions_arr[INFOTAINMENT_NUMBER_OF_QUESTIONS]=
{"Alahly won?","Is Salah fast ?","Is sea blue?","Is task good?", "r u happy?"};
/************************************************************************/
/*   Infotainment Answers Array of chars					   					  */
/************************************************************************/
const char Infotainment_Answers_arr[INFOTAINMENT_NUMBER_OF_QUESTIONS] = {'Y', 'Y', 'Y', 'Y', 'Y'};

/**************************************************************************
 * Function Name : Infotainment_Start
 *
 * Description	 : Starting Infotainment Task
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment_Start(void) 
{
	static uint8 result =0;
	sampling_rate=2;
	Infotainment_Result_g=0;
	Infotainment_Question_Index_g=0;
	Infotainment_Score = 0;
	LCD_clearScreen();
	LCD_displayString("Want play game?");
	result = key_getpressed();
	if (result == YES)
	{
		Infotainment_NewDataFlag_g=1 ;
		Infotainment_Status = INFOTAINMENT_QUESTION;
	}	
	else if (result == NO )
	{
		/*nothing */
	}	
}
/**************************************************************************
 * Function Name : Infotainment_PrintQuestion
 *
 * Description	 : Printing Questions of the game
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment_PrintQuestion (void)
{	

	if (Infotainment_NewDataFlag_g==1u)
	{
		LCD_clearScreen();
		LCD_displayString(Infotainment_Questions_arr[Infotainment_Question_Index_g]);
		Infotainment_Question_Index_g ++;
		Infotainment_Status = INFOTAINMENT_GET_ANSWER ;
	}

	else 
	{
		/*Do nothing*/
	}	
}
/**************************************************************************
 * Function Name : Infotainment_GetAnswer
 *
 * Description	 : Displaying Answer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment_GetAnswer (void)
{
	uint8 result ;

	result = key_getpressed();
	if(result==1)
	{
		DIO_SetPinDirection(PinB4,LOW);
		Toggle_Bit(PORTB,(PinB4-8));
	}
	else
	{
		//DIO_SetPinDirection(PinB4,LOW);
		DIO_WritePin(PinB4,LOW);
	}
	DIO_SetPinDirection(PinB0,OUTPUT);
	if (result == YES)
	{
		DIO_WritePin(PinB0,HIGH);
		Infotainment_Result_g = 'Y' ;
		Infotainment_NewDataFlag_g = 1u;
		Infotainment_Status = INFOTAINMENT_SCORE ;
	}
	else if (result == NO)
	{
		Infotainment_Result_g = 'N' ;
		Infotainment_NewDataFlag_g = 1u;
		Infotainment_Status = INFOTAINMENT_SCORE ;
	}
	else 
	{
		//Infotainment_NewDataFlag_g = 0u;
	}

}
/**************************************************************************
 * Function Name : Infotainment_ScoreDisplay
 *
 * Description	 : Displaying Score
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment_ScoreDisplay (void)
{


	if (Infotainment_Result_g == Infotainment_Answers_arr[Infotainment_Question_Index_g -1])
	{
		Infotainment_Score ++ ;
		LCD_clearScreen();
		LCD_displayString("Correct:)");
		Infotainment_NewDataFlag_g = 1u;
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Wrong :(");
		Infotainment_NewDataFlag_g = 1u;
	}
	if (Infotainment_Question_Index_g == INFOTAINMENT_NUMBER_OF_QUESTIONS)
	{
		Infotainment_Status = INFOTAINMENT_FINAL ;
	}
	else if (Infotainment_Question_Index_g < INFOTAINMENT_NUMBER_OF_QUESTIONS)
	{
		Infotainment_Status = INFOTAINMENT_QUESTION ;
	}
}
/**************************************************************************
 * Function Name : Infotainment_FinalScore
 *
 * Description	 : Displaying Final score
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment_FinalScore(void)
{
	LCD_clearScreen();
	LCD_displayString("Final Score = ");
	LCD_intgerToString(Infotainment_Score);
	Infotainment_NewDataFlag_g = 0u;

	Infotainment_Status = INFOTAINMENT_IDLE ;
}

