/*
 * CPU_SLEEP.h
 *
 * Created: 9/24/2019 2:03:09 PM
 *  Author: Bobpo
 */ 


#ifndef CPU_SLEEP_H_
#define CPU_SLEEP_H_

#define MCUCR (*(volatile uint8*) 0x55)
#define SE  7
#define SM2 6
#define SM1 5
#define SM0 4
extern void cpu_sleep(void);



#endif /* CPU_SLEEP_H_ */