/*
 * Timer.c
 *
 * Created: 18/08/2019 10:02:39 ص
 *  Author: AhmedGaber
 */ 

#include "Timer.h" 
extern  cnfg_type timer_cnfg;

void timer0_init(void){
	OCR0  = 0x00;
	TCCR0 = 0x00;
	TCNT0 = 0x00; 
	
	if (timer_cnfg.mode== Normal_mode){	
		Clear_Bit(TCCR0,WGM00); Clear_Bit(TCCR0,WGM01); Clear_Bit(TCCR0,COM00); Clear_Bit(TCCR0,COM01);		
	}
	else if (timer_cnfg.mode== PWM_PhaseCorrect) {
		Set_Bit(TCCR0,WGM00); Clear_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Set_Bit(TCCR0,COM01);
	}
	else if (timer_cnfg.mode== CTC) {
		Clear_Bit(TCCR0,WGM00); Set_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Clear_Bit(TCCR0,COM01);
	}
	else if (timer_cnfg.mode== Fast_PWM) {
        Set_Bit(TCCR0,WGM00); Set_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Set_Bit(TCCR0,COM01);			
	}
	

	if      (timer_cnfg.CMI==Enabled)  { Set_Bit(TIMSK,OCIE0);Set_Bit(SREG,7); }
	else if (timer_cnfg.CMI==Disabled) { Clear_Bit(TIMSK,OCIE0); }
		
    if      (timer_cnfg.OVI==Enabled)  { Set_Bit(TIMSK,TOIE0); Set_Bit(SREG,7); }
	else if (timer_cnfg.OVI==Disabled) { Clear_Bit(TIMSK,TOIE0); }

}

void timer0_start(){
	
if (timer_cnfg.prescaler== no_prescaler ) {Set_Bit(TCCR0,CS00); Clear_Bit(TCCR0,CS01); Clear_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== 8 )    {Clear_Bit(TCCR0,CS00); Set_Bit(TCCR0,CS01); Clear_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== 64 )   {Set_Bit(TCCR0,CS00); Set_Bit(TCCR0,CS01); Clear_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== 256 )  {Clear_Bit(TCCR0,CS00); Clear_Bit(TCCR0,CS01); Set_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== 1024 ) {Set_Bit(TCCR0,CS00); Clear_Bit(TCCR0,CS01); Set_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== XFE )  {Clear_Bit(TCCR0,CS00); Set_Bit(TCCR0,CS01); Set_Bit(TCCR0,CS02);}
else if (timer_cnfg.prescaler== XRE )  {Set_Bit(TCCR0,CS00); Set_Bit(TCCR0,CS01); Set_Bit(TCCR0,CS02);}
}

void timer0_stop()
{
	/* NO prescaler */
	Clear_Bit(TCCR0,CS00); Clear_Bit(TCCR0,CS01); Clear_Bit(TCCR0,CS02);
}
void timer0_SetOCR(uint8 Tick)
{
	switch (Tick)
	{
		case 1 : OCR0 = 31 ; break ;
		
		case 2 : OCR0 = 63 ;  break;
		
		case 3 : OCR0 = 94 ;  break ;
		
		case 4 : OCR0 = 125;  break ;
		
		case 5 : OCR0 = 156;  break ;
		
		case 6 : OCR0 = 187;  break ;
		
		case 7 : OCR0 = 219;  break ;
		
		case 8 : OCR0 =250 ;  break ;
		
		default: OCR0 =250 ;  break ;
	
	}
	
}
void timer1_init(void){
	//clear all registers
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	ICR1H  = 0x00;
	ICR1L  = 0x00;
	/*if (timer_cnfg.mode== Normal_mode){
		Clear_Bit(TCCR1A,WGM00); Clear_Bit(TCCR1A,WGM01); Clear_Bit(TCCR0,COM00); Clear_Bit(TCCR0,COM01);
	}
	else if (timer_cnfg.mode== PWM_PhaseCorrect) {
		Set_Bit(TCCR0,WGM00); Clear_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Set_Bit(TCCR0,COM01);
	}
	else if (timer_cnfg.mode== CTC) {
		Clear_Bit(TCCR0,WGM00); Set_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Clear_Bit(TCCR0,COM01);
	}
	else if (timer_cnfg.mode== Fast_PWM) {
		Set_Bit(TCCR0,WGM00); Set_Bit(TCCR0,WGM01); Set_Bit(TCCR0,COM00); Set_Bit(TCCR0,COM01);
	}
	*/


}

void timer_delay(uint32 n){
	TCNT0 = 0;
	OCR0 = 125;
	while (n != 0)
	{
      while ((Get_Bit(TIFR,OCF0)) != 1 );
	  n--;
	  Set_Bit(TIFR,OCF0);		
	}
		
}

void __vector_10 (void) __attribute__ ((signal,used)) ; /* timer 0 interrupt CTC */

void __vector_10 (void){
	
	TCNT0=0;
	/*Long Term scheduler*/
	 timer_cnfg.CTC_CallbackPtr ();
}