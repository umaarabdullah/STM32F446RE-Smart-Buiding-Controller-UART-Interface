#include "GPIO_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Set the prescaler TIMx_PSC 
void TIMER6_PSC_90(void);		

// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void);	

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void);

// Set precise Delay
void TIMER6_Delay_us(uint16_t timeMicroSec);	
void TIMER6_Delay_ms(uint16_t timeMilliSec);		
void TIMER6_Delay_s(uint16_t timeSec);				
