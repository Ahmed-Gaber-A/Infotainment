/*
 * Timer.h
 *
 * Created: 18/08/2019 10:10:07 ص
 *  Author: AhmedGaber
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "function_macros.h"
#include "standard_types.h"
//timer registers memory map
#define SREG   (*(volatile uint8*)0x5f)
#define TIMSK  (*(volatile uint8*)0x59) // Timer/counter interrupt mask register
#define TIFR   (*(volatile uint8*)0x58)  // Timer/counter interrupt flag register 
#define SFIOR  (*(volatile uint8*)0x50) //special function IO register
//timer 0 
#define TCCR0  (*(volatile uint8*)0x53) // Timer/counter control register 0 
#define TCNT0  (*(volatile uint8*)0x52) // Timer/counter register 0 
#define OCR0   (*(volatile uint8*)0x5C)  //output compare register 0 
//timer 2
#define TCCR2  (*(volatile uint8*)0x45) // Timer/counter control register 2
#define TCNT2  (*(volatile uint8*)0x44) // Timer/counter register 2
#define OCR2   (*(volatile uint8*)0x43)  //output compare register 2
#define ASSR   (*(volatile uint8*)0x42)  //Asynchronous
//Timer 1
#define TCCR1A (*(volatile uint8*)0x4F) // Timer/counter control register 1
#define TCCR1B (*(volatile uint8*)0x4E) // Timer/counter register 2
#define TCNT1H (*(volatile uint8*)0x4D)  //output compare register 2
#define TCNT1L (*(volatile uint8*)0x4C) // Timer/counter control register 2
#define OCR1AH (*(volatile uint8*)0x4B) // Timer/counter register 2
#define OCR1AL (*(volatile uint8*)0x4A)  //output compare register 2
#define OCR1BH (*(volatile uint8*)0x49) // Timer/counter control register 2
#define OCR1BL (*(volatile uint8*)0x48) // Timer/counter register 2
#define ICR1H  (*(volatile uint8*)0x47)  //Input capture
#define ICR1L  (*(volatile uint8*)0x46)

//Timer 0 pins 
//TCCR0 
#define FOC0  7  //Force Output Compare
#define WGM00 6  //Waveform Generation Mode
#define WGM01 3 
#define COM01 5  // Compare MAtch output mode
#define COM00 4 
#define CS02  2  //clock select
#define CS01  1 
#define CS00  0 

//TIMSK Timer/Counter Interrupt Mask Register 
#define OCIE2  7  
#define TOIE2  6 
#define TICIE  5 
#define OCIE1A 4 
#define OCIE1B 3 
#define TOIE1  2 
#define OCIE0  1  //Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE0  0  //Timer/Counter0 Overflow Interrupt Enable

//TIFR Timer/Counter Interrupt Flag Register
#define OCF2  7 
#define TOV2  6 
#define ICF1  5  
#define OCF1A 4  
#define OCF1  3  
#define TOV1  2 
#define OCF0  1  //Timer/counter 0 output compare flag
#define TOV0  0  //Timer/counter 0 overflow flag

//Prescaler Reset Timer/Counter1 and Timer/Counter0
#define PSR10 0 //(SFIOR&(1<<0))
#define PSR2  1 //(SFIOR&(1<<1))

//TCCR1A
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A  3
#define FOC1B  2
#define WGM11  1
#define WGM10  0

//TCCR1B
#define ICNC1 7 
#define ICES1 6
// reserved 5 
#define WGM13 4 
#define WGM12 3 
#define CS12  2 
#define CS11  1 
#define CS10  0 
//modes
#define Normal_mode 0
#define PWM_PhaseCorrect 1
#define CTC 2
#define Fast_PWM 3

//prescaler
#define no_prescaler  0
#define XFE 2
#define XRE 3

#define Enabled 1
#define Disabled 0

typedef void (* CTC_CallbackPtr_t) (void);

 typedef struct   {
 uint8 mode  ;	
 uint16 prescaler;
 uint8 CMI ; //Compare Match Interrupt
 uint8 OVI ; //overflow  Interrupt 
 CTC_CallbackPtr_t CTC_CallbackPtr ;
 
	}cnfg_type;


extern void timer0_init(void); 
extern void timer0_start(void);
extern void timer0_stop(void);
extern void timer1_init(void);
extern void timer0_SetOCR(uint8);
extern void timer_delay(uint32 n); //n milliseconds
#endif /* TIMER_H_ */