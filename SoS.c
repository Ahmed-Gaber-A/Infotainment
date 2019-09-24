/*
 * SoS.c
 *
 * Created: 15/09/2019 05:45:17 م
 *  Author: AhmedGaber
 */ 

#include "SoS.h"
#include "SoS_PBCfg.h"
#include "Timer.h"
#include "CPU_SLEEP.h"

SoS_str_TaskInfo_t SoS_Tasks_arr [MAX_NUM_TASKS]  ; 


uint8 u8_Tasks_count = 0u;
uint8 Tasks_max_priority = 0u;
/************************************************************************
* Function name : SoS_init
*
* Description : It initializes the SoS module and Timer initialization
*
*
* Inputs : NULL
*
* Outputs : NULL
*
* Return :  NULL
************************************************************************/

void SoS_init(void)
{
	uint8 tasknum;
	for (tasknum=0;tasknum<u8_Tasks_count;tasknum++)
	{
		SoS_Tasks_arr[tasknum].SoS_funcPtr =  NULL; /* initialize all Tasks prt by NULL*/
		SoS_Tasks_arr[tasknum].Task_Status =  READY; /* initialize all Tasks status by READY */
	}	
	timer0_init();
	timer0_SetOCR(SoS_TickTime_ms);
	
}

/************************************************************************
* Function name : SoS_Deinit
*
* Description : It stops SoS functionality bu stop the timer
*
*
* Inputs : NULL
*
* Outputs : NULL
*
* Return :  NULL
************************************************************************/
extern void SoS_Deinit (void)
{
	timer0_stop();
}

/************************************************************************
* Function name : SoS_CreatTask
*
* Description : It initializes the SoS module and Timer initialization
*
*
* Inputs : pointer to function , periodicity , priority
*
* Outputs : NULL
*
* Return : status if it is correctly created
************************************************************************/
SoS_enmm_status_t SoS_CreateTask(SoS_funcPtr_t FuncPtr, uint32 Periodicity , uint8 priority)
{ 
	SoS_enmm_status_t checker;
	if (u8_Tasks_count < MAX_NUM_TASKS)  /*check if the user doesn't exceed max number of tasks*/
	{  
	    SoS_Tasks_arr[u8_Tasks_count].SoS_funcPtr =  FuncPtr;
	    SoS_Tasks_arr[u8_Tasks_count].Task_Periodicity = Periodicity;
		SoS_Tasks_arr[u8_Tasks_count].Task_TimeDelay = Periodicity;
	    SoS_Tasks_arr[u8_Tasks_count].Task_Priority = priority ;
	    SoS_Tasks_arr[u8_Tasks_count].Task_Status = READY ; 
	    u8_Tasks_count++;
	    checker = SoS_OK;
	}
	else 
    {
		  checker =  SoS_NOK; 
	}	
	return checker;
}

/************************************************************************
* Function name : SoS_DeleteTask
*
* Description : It deletes a task from the scheduler by assign the pointer to NULL so it is not called by SoS
*
* Inputs : pointer to function (function name)
*
* Outputs : NULL
*
* Return : status if the task is correctly deleted
************************************************************************/

SoS_enmm_status_t SoS_DeleteTask(SoS_funcPtr_t FuncPtr)
{ 
	SoS_enmm_status_t checker = SoS_NOK ; 
	uint8 tasknum =0; 
	for (tasknum=0;tasknum<u8_Tasks_count;tasknum++)
	{
		if (SoS_Tasks_arr[tasknum].SoS_funcPtr == FuncPtr) /* Search by task name */
		{
	      SoS_Tasks_arr[tasknum].SoS_funcPtr = NULL;
		  SoS_Tasks_arr[tasknum].Task_Periodicity = 0u;
		  SoS_Tasks_arr[tasknum].Task_Priority = 0u;
		  SoS_Tasks_arr[u8_Tasks_count].Task_Status = READY;
		checker = SoS_OK ;
		}	
	}
return checker;	
}

/************************************************************************
* Function name : SoS_Run
*
* Description : It handles tasks and decide which to run based on priority
*
*
* Inputs : NULL
*
* Outputs : NULL
*
* Return : NULL
************************************************************************/

void SoS_Run(void)
{ timer0_start();
	uint8 tasknum;
	while (1)
	{ /* Loop over the Tasks*/
	  for (tasknum=0u;tasknum<u8_Tasks_count  ;tasknum++)
	    {     /*  search for READY Task and have maximum priority  */
		   if (SoS_Tasks_arr[tasknum].Task_Status == READY && SoS_Tasks_arr[tasknum].Task_Priority == Tasks_max_priority )
		   { if (SoS_Tasks_arr[tasknum].SoS_funcPtr != NULL) /* if the task was not deleted or null */
			   { /*run the task then turn it to waiting state*/
			     SoS_Tasks_arr[tasknum].Task_Status = RUNNING;
			     SoS_Tasks_arr[tasknum].SoS_funcPtr();
			     SoS_Tasks_arr[tasknum].Task_Status = WAITING;
			     Tasks_max_priority --; /* Decrement the priority to check again if their is any ready task with lower priority */
				 tasknum =0u;
			   }			
		   }		   
	    }
		cpu_sleep();
	}
	
}

/************************************************************************
* Function name : SoS_LongTerm
*
* Description : It handles tasks and decide which to run based on times
*				It is called bu the ISR in the timer
*
* Inputs : NULL
*
* Outputs : NULL
*
* Return : NULL
************************************************************************/
void SoS_LongTerm(void)
{
	uint8 tasknum;
	Tasks_max_priority =0u;
	for (tasknum=0;tasknum<u8_Tasks_count;tasknum++)
	{	
		SoS_Tasks_arr[tasknum].Task_TimeDelay -- ; /* decrement all Tasks time delay */
		
		if (SoS_Tasks_arr[tasknum].Task_TimeDelay == 0) /* check all Tasks if it is  their turn to run */
		{
			SoS_Tasks_arr[tasknum].Task_Status = READY; /*change state to READY*/
			SoS_Tasks_arr[tasknum].Task_TimeDelay = SoS_Tasks_arr[tasknum].Task_Periodicity ; /*Update Tasks time delay*/
			
			if (SoS_Tasks_arr[tasknum].Task_Priority > Tasks_max_priority) /*Set maximum priority value*/
			{
				Tasks_max_priority = SoS_Tasks_arr[tasknum].Task_Priority;
			}
		}
		else if (SoS_Tasks_arr[tasknum].Task_TimeDelay > 0)  /* if it is not their turn to run then it is in WAITING state*/
		{
			SoS_Tasks_arr[tasknum].Task_Status = WAITING;
		}
	}
	
}