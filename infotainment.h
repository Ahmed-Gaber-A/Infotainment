/***********************************************
 *  Module:Infotainment
 *
 *  File Name:Infontainement.h
 *
 *  Description: Infotainment prototypes and definitions
 *
 *  Created on : 24/9/2019
 *
 *  Author: Ahmed Ekram & Ahmed Gaber
 ***********************************************/


#ifndef INFOTAINMENT_H_
#define INFOTAINMENT_H_
/************************************************************************/
/*					Included Libraries                                                                     */
/************************************************************************/

//#include "DIO_operations.h"
#include "standard_types.h"
#include "keypad.h"
#include "LCD.h"



/************************************************************************/
/*         preprocessor definitions                                                                    */
/************************************************************************/
/* *****************Infotainment status ******************/
#define INFOTAINMENT_IDLE 0
#define INFOTAINMENT_QUESTION 1
#define INFOTAINMENT_GET_ANSWER 2
#define INFOTAINMENT_SCORE   3
#define INFOTAINMENT_FINAL 4
 
/******Number of questions*****/

#define INFOTAINMENT_NUMBER_OF_QUESTIONS 5

/*Answers definitions*/

#define YES 1 //button 1 is Yes
#define NO 9 //button 9 is NO
/************************************************************************/
/*				Global Variables                                        */
/************************************************************************/
extern uint8 Infotainment_Status ;
/************************************************************************/
/*					Functions Declarations                                                                     */
/************************************************************************/ 
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
extern void Infotainment_PrintQuestion (void);
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
extern void Infotainment_GetAnswer (void);
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
extern void Infotainment_ScoreDisplay (void);
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
extern void Infotainment_FinalScore(void);
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
extern void Infotainment_Start(void) ;
#endif /* INFOTAINMENT_H_ */
