/*
 * infotainment.c
 *
 * Created: 9/24/2019 11:40:40 AM
 *  Authors: Ahmed Ekram & Ahmed Gaber
 */ 

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
static uint8 Infotainment_NewDataFlag_g  ;
static uint8 Infotainment_Result_g ;
static uint8 Infotainment_Question_Index_g ;
static uint8 Infotainment_Score = 0;

/************************************************************************/
/*   Questions Array of strings					   					  */
/************************************************************************/
const char *Infotainment_Questions_arr[INFOTAINMENT_NUMBER_OF_QUESTIONS]=
{" AlAHly Won? "," Salah is Fast? "," Sea is Blue? "," Task is Good? ", " U R happy? "};
/************************************************************************/
/*   Infotainment Answers Array of chars					   					  */
/************************************************************************/
const char Infotainment_Answers_arr[INFOTAINMENT_NUMBER_OF_QUESTIONS] = {'Y', 'Y', 'Y', 'Y', 'Y'};
/************************************************************************"
/*						Function Definitions                          
************************************************************************/

void Infotainment_Start(void) 
{
	
	static uint8 result ; 
	Infotainment_Question_Index_g = 0 ;
	Infotainment_Result_g = 0;
	Infotainment_Score =0 ;
	
	result = key_getpressed();
	if (result == YES)
	{
	LCD_clearScreen();
	LCD_displayString(" Want play game?");
	Infotainment_Status = INFOTAINMENT_QUESTION;
	Infotainment_NewDataFlag_g = 1u;
	}	
	else if (result == NO )
	{
		/*nothing */
	}	
}

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

void Infotainment_GetAnswer (void)
{
	uint8 result ;
	result = key_getpressed();
	if (result == YES)
	{
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

void Infotainment_ScoreDisplay (void)
{
	
	
	if (Infotainment_Result_g == Infotainment_Answers_arr[Infotainment_Question_Index_g -1])
	 {
		 Infotainment_Score ++ ;
		 LCD_clearScreen();
		 LCD_displayString(" Correct:)");
		 Infotainment_NewDataFlag_g = 1u;
	 }
	 else 
	 {
		 LCD_clearScreen();
		 LCD_displayString(" Wrong :(");
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

void Infotainment_FinalScore(void)
{
	LCD_clearScreen();
	LCD_displayString(" Final Score = ");
	LCD_intgerToString(Infotainment_Score);
	Infotainment_NewDataFlag_g = 0u; 
	Infotainment_Status = INFOTAINMENT_IDLE ; 
}

