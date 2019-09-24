/***********************************************
 *  Module:Application
 *
 *  File Name:APP.c
 *
 *  Description: Application tasks
 *
 *  Created on : 24/9/2019
 *
 *  Author: Ahmed Ekram & Ahmed Gaber
 ***********************************************/

/************************************************************************/
/*			Included Libraries                                           */
/************************************************************************/
#include "Timer0_registers.h"
#include "DIO_operations.h"
#include "keypad.h"
#include "LCD.h"
#include "OS.h"
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
	OS_init();
	LCD_init();
	//keypad_init();
	Create_Task(Task_1ms_GetKey,1,2);
	Create_Task(Task_10ms_Game,0,999);
	OS_Run();
	return 0 ;
}
