/***********************************************
 *  Module:OS
 *
 *  File Name:OS.c
 *
 *  Description: OS Functions
 *
 *  Created on : 15/9/2019
 *  Modified on: 16/9/2019
 *
 *  Author: Ahmed Ekram
 ***********************************************/

#include "OS.h"

#include "OS_PBCfg.h"
/*Array of structures to hold tasks*/
OS_Str_Tasks_Info_t Str_Array_Tasks[MAX_NUM_TASKS];
/*Index which increment with each task creation and is used in OS running operation*/
static uint8 u8_Tasks_Index=0u;
volatile static uint16 OS_TickCounter=1;
uint8 SoS_TickTime_ms =1u ;
/**************************************************************************
 * Function Name : OS_init
 *
 * Description	 : Operate timer ,Set Tick time and initialize tasks buffer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void OS_init(void)
{
	/*Looping index for Initializing Array of structures for tasks */
	uint8 u8_Array_Index;
	/*Enabling Global Interrupt*/
	global_interrupt_enable();
	/*Initilizing Timer*/
	timer0_init();
	/*Setting Compare match value according to match Tick time*/
	Set_OCR_Value(u8_OS_TickTIme_ms);
	/*passing value of call back function to setcallback function*/
	OS_SetCallBack(OS_Long_Term);
	/*Initializing Array of structures for tasks*/
	for(u8_Array_Index=0;u8_Array_Index<MAX_NUM_TASKS;u8_Array_Index++)
	{
		Str_Array_Tasks[u8_Array_Index].OS_PTR_Function=NULL;
		Str_Array_Tasks[u8_Array_Index].Task_Priority=PRIORITY_ZERO_HIGHEST;
		Str_Array_Tasks[u8_Array_Index].Task_Periodicity=0u;
		Str_Array_Tasks[u8_Array_Index].Task_Status=WAITING;
	}
}
/**************************************************************************
 * Function Name : OS_Deinit
 *
 * Description	 : Disabling timer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void OS_Deinit(void)
{
	/*Clearing prescaler value to disable timer and disable OS*/
	timer0_Deinit();
}
/**************************************************************************
 * Function Name : Create_Task
 *
 * Description	 : Creating Tasks and assign it in the buffer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
OS_Status_t Create_Task(PTR_Function OS_PTR_Function,uint8 Task_Priority,uint16 Task_Periodicity)
{
	OS_Status_t Ret_Value;
	/*Assigning Value for tasks*/
	/*Initializing Tasks by pointing pointer to function to null and move it to waiting status*/
	if(u8_Tasks_Index<MAX_NUM_TASKS)
	{
		Str_Array_Tasks[u8_Tasks_Index].OS_PTR_Function = OS_PTR_Function;
		Str_Array_Tasks[u8_Tasks_Index].Task_Priority = Task_Priority;
		Str_Array_Tasks[u8_Tasks_Index].Task_Periodicity = Task_Periodicity;
		Str_Array_Tasks[u8_Tasks_Index].Task_Status = WAITING;
		u8_Tasks_Index++;
		Ret_Value=OS_OK;
	}
	else
	{
		Ret_Value=OS_NOT_OK;
	}
	return Ret_Value;
}
/**************************************************************************
 * Function Name : Delete_Task
 *
 * Description	 : Deleting Tasks and removing them from buffer
 *
 * INPUTS		 : Pointer to function , Task priority ,Task periodicity
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
OS_Status_t Delete_Task(PTR_Function OS_PTR_Function)
{
	/*Looping index for Deleting tasks of structures for tasks */
	uint8 u8_Array_Index;
	OS_Status_t Ret_Value=OS_NOT_OK;
	/*Deleting Tasks by pointing pointer to function to null and move it to deleted status*/
	for(u8_Array_Index=0;u8_Array_Index<u8_Tasks_Index;u8_Array_Index++)
	{
		/*Deleting Tasks by pointing pointer to function to null and move it to deleted status*/
		/*Searching for address of task needed to be deleted */
		if(Str_Array_Tasks[u8_Array_Index].OS_PTR_Function==OS_PTR_Function)
		{
			Str_Array_Tasks[u8_Array_Index].OS_PTR_Function=NULL;
			Str_Array_Tasks[u8_Array_Index].Task_Priority=PRIORITY_ZERO_HIGHEST;
			Str_Array_Tasks[u8_Array_Index].Task_Periodicity=0u;
			Str_Array_Tasks[u8_Array_Index].Task_Status=DELETED;
			Ret_Value=OS_OK;
		}
	}
	return Ret_Value;
}
/**************************************************************************
 * Function Name : OS_Run
 *
 * Description	 : Running the scheduler
 *
 * INPUTS		 : pointer to function
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void OS_Run(void)
{
	/*Looping index for searching for tasks */
	uint8 u8_Array_Index;
	/*Checking for index of tasks*/
	uint8 u8_Priority_Index;
	while(1)
	{
		/*looping to check for ready tasks*/
		for(u8_Array_Index = 0 ;u8_Array_Index < u8_Tasks_Index ; u8_Array_Index++)
		{
			if( Str_Array_Tasks[u8_Array_Index].Task_Status == READY)
			{
				/*looping to check for ready tasks and finding highest priority to move them to
				 * running state and then call the task to operate and then move it to waiting state
				 * after finishing implementation*/
				for(u8_Priority_Index = PRIORITY_ZERO_HIGHEST ; u8_Priority_Index <= PRIORITY_FIVE_LOWEST ; u8_Priority_Index++)
				{
					if( Str_Array_Tasks[u8_Array_Index].Task_Priority == u8_Priority_Index )
					{
						Str_Array_Tasks[u8_Array_Index].Task_Status = RUNNING;
						Str_Array_Tasks[u8_Array_Index].OS_PTR_Function();
						Str_Array_Tasks[u8_Array_Index].Task_Status = WAITING;
					}
				}
			}
		}
	}
}
/**************************************************************************
 * Function Name : OS_Long_Term
 *
 * Description	 : Callback function to update status will be called from
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void OS_Long_Term(void)
{
	/*Looping index for searching for tasks */
	uint8 u8_Array_Index;
	/*looping to check for tasks that met their time period*/
	for(u8_Array_Index = 0 ;u8_Array_Index < u8_Tasks_Index ; u8_Array_Index++)
	{
		/*if time counter met time perdiocity of function move it to ready state*/
		if( OS_TickCounter % Str_Array_Tasks[u8_Array_Index].Task_Periodicity==0)/**/
		{
			Str_Array_Tasks[u8_Array_Index].Task_Status = READY;
		}
		/*if time counter didn't meet time perdiocity of function move it to waiting state*/
		else
		{
			Str_Array_Tasks[u8_Array_Index].Task_Status = WAITING;
		}
	}
	OS_TickCounter++;
}
