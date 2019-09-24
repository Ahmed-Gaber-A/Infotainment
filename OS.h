/***********************************************
 *  Module:OS
 *
 *  File Name:OS.h
 *
 *  Description: OS Prototypes and Typedefs
 *
 *  Created on : 15/9/2019
 *  Modified on: 16/9/2019
 *
 *  Author: Ahmed Ekram
 ***********************************************/

#ifndef OS_H_
#define OS_H_
/**************************************************************************
 * 				            Included files							      *
 *************************************************************************/
#include "standard_types.h"
#include "DIO_operations.h"
#include "function_macros.h"
#include "Memory_map.h"
#include "Timer0_registers.h"

typedef void (*PTR_Function)(void);
/**************************************************************************
 * 				            User Defined types							  *
 *************************************************************************/
/*********************Enum for Status of tasks*********************/
typedef enum{
	READY,
	RUNNING,
	WAITING,
	DELETED
}OS_Enum_Task_Status_t;
/*********************Enum for Status of operations result*********************/
typedef enum{
OS_OK,
OS_NOT_OK
}OS_Status_t;
/*********************Enum for list of priorities*********************/
typedef enum{
	PRIORITY_ZERO_HIGHEST,
	PRIORITY_ONE,
	PRIORITY_TWO,
	PRIORITY_THREE,
	PRIORITY_FOUR,
	PRIORITY_FIVE_LOWEST,
}OS_Priorities_t;
/*********************Struct holding tasks info*********************/
typedef struct{
	PTR_Function OS_PTR_Function;
	OS_Enum_Task_Status_t Task_Status;
	uint16 Task_Periodicity;
	uint8 Task_Priority;
}OS_Str_Tasks_Info_t;

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
extern void OS_init(void);
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
extern OS_Status_t Create_Task(PTR_Function OS_PTR_Function,uint8 Task_Priority,uint16 Task_Periodicity);
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
extern OS_Status_t Delete_Task(PTR_Function OS_PTR_Function);
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
extern void OS_Run(void);
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
extern void OS_Long_Term(void);
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
extern void OS_Deinit(void);

#endif /* OS_H_ */
