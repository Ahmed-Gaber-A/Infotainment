/*
 * CFile1.c
 *
 * Created: 9/24/2019 2:00:36 PM
 *  Author: Bobpo
 */ 

#include "function_macros.h"
#include "standard_types.h"
#include "CPU_SLEEP.h"

void cpu_sleep(void)
{
	Set_Bit(MCUCR,SE);
	Clear_Bit(MCUCR,SM0);
	Clear_Bit(MCUCR,SM1);
	Clear_Bit(MCUCR,SM2);
}