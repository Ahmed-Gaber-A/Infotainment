/*
 * Timer_cnfg.c
 *
 * Created: 18/08/2019 01:26:25 م
 *  Author: AhmedGaber
 */ 
#include "Timer.h"
extern void SoS_LongTerm(void);

const cnfg_type timer_cnfg = {
				 CTC,
				 256,
				 Enabled, //Compare Match Interrupt
				 Disabled , //overflow  Interrupt 
				 &SoS_LongTerm
         	};