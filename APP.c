/*
 * APP.c
 *
 * Created: 9/24/2019 12:55:03 PM
 *  Authors: Ahmed Ekram & Ahmed Gaber
 */ 
/************************************************************************/
/*			Included Libraries                                           */
/************************************************************************/
#include "Timer.h"
#include "DIO_operations.h"
#include "keypad.h"
#include "LCD.h"
#include "SoS.h"
#include "infotainment.h"
/************************************************************************/
/*				OS tasks definitions                                     */
/************************************************************************/
void Task_1ms_GetKey(void)
{
	if (Infotainment_Status == INFOTAINMENT_GET_ANSWER)
	{
		Infotainment_GetAnswer();
	}
	/*get keypad */
}

void Task_10ms_Game(void)
{ 
	if (Infotainment_Status == INFOTAINMENT_IDLE)
	{
		Infotainment_Start();
	}
	else if (Infotainment_Status == INFOTAINMENT_QUESTION )
	{
	    Infotainment_PrintQuestion ();
	}
	else if (Infotainment_Status == INFOTAINMENT_SCORE )
	{
		Infotainment_ScoreDisplay();
	}
	else if (Infotainment_Status == INFOTAINMENT_FINAL)
	{
		
		Infotainment_FinalScore();
	}
		
}

int main (void)
{
	
	
	keypad_init();
	LCD_init();
	SoS_init();
	SoS_CreateTask(Task_1ms_GetKey,10,1);
	SoS_CreateTask(Task_10ms_Game,1000,2);
	
		
	SoS_Run();
		
	
	return 0 ;
}