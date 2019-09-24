/*
 * SoS.h
 *
 * Created: 15/09/2019 05:46:29 م
 *  Author: AhmedGaber
 */ 


#ifndef SOS_H_
#define SOS_H_
/************************************************************************/
/*					Header Files inclusion                                                                      */
/************************************************************************/
#include "DIO_operations.h"
#include "standard_types.h"
/************************************************************************/
/*					NULL Operator definition                                                                    */
/************************************************************************/
#define NULL ((void*)0)
/************************************************************************/
/*						 User Type definitions                                                                     */
/************************************************************************/
/**  **Tasks status enum**   **/
typedef enum {READY, RUNNING, WAITING} SoS_enmm_Task_status_t; 
/**	  status Retrun type 	**/
typedef enum {SoS_NOK=0 , SoS_OK=1 } SoS_enmm_status_t;
/**	 function call back ptr definintion	**/
typedef void (*SoS_funcPtr_t) (void) ;

/** Tasks info structure  **/
typedef struct {
	SoS_funcPtr_t SoS_funcPtr ;
	SoS_enmm_Task_status_t Task_Status ;
	uint32 Task_Periodicity;
	uint32 Task_TimeDelay;
	uint8 Task_Priority;
	}SoS_str_TaskInfo_t;
/************************************************************************/
/*						Function prototypes                                                                     */
/************************************************************************/

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
extern void SoS_init (void);

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
extern void SoS_Deinit (void);
/************************************************************************
* Function name : SoS_CreatTask
*
* Description : It initializes the SoS module and Timer initialization
*
*
* Inputs : pointer to function , periodicity , priority
*
* Outputs :
*
* Return :
************************************************************************/
extern SoS_enmm_status_t SoS_CreateTask (SoS_funcPtr_t FuncPtr, uint32 Periodicity , uint8 priority);
/************************************************************************
* Function name : SoS_DeleteTask
*
* Description : It deletes a task from the scheduler
*
* Inputs : pointer to function
*
* Outputs :
*
* Return :
************************************************************************/
extern SoS_enmm_status_t SoS_DeleteTask (SoS_funcPtr_t FuncPtr);

/************************************************************************
* Function name : SoS_Run
*
* Description : It handles tasks and decide which to run
*
*
* Inputs : pointer to function , periodicity , priority
*
* Outputs :
*
* Return :
************************************************************************/
void SoS_Run(void);


#endif /* SOS_H_ */