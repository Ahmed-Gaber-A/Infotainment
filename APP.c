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

/************************************************************************
*  GetKey Task   is called every 1ms 
*  checks if the game asks for answer 
*   if so it calls get answer function that operates on keypad                               
************************************************************************/

void Task_1ms_GetKey(void)
{
	if (Infotainment_Status == INFOTAINMENT_GET_ANSWER)
	{
		Infotainment_GetAnswer();
	}
	/*get keypad answer */
}

/************************************************************************
*  Game Task   is called every 250ms
*  checks if the game status
*  it calls one of game function depending on the state
************************************************************************/
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
	/*Initializing modules*/
	keypad_init();
	LCD_init();
	SoS_init();
	
	/*Infotainment check answer Task is a periodic task that is called every 1 ms 
	* It Takes answers from user through keypad 
	* It handles the denouncing effect of the push button
	*It have Lower Priority (1).
	*/
	SoS_CreateTask(Task_1ms_GetKey,1,1);
	/*Infotainment Game Task is a periodic task that is called every 250 ms 
	* It is suitable periodicity for the User to play the Game
	* with out overload the CPU.
	*It have Higher Priority (2).
	*/
	SoS_CreateTask(Task_10ms_Game,250,2); 
	
		
	SoS_Run();
		
	
	return 0 ;
}