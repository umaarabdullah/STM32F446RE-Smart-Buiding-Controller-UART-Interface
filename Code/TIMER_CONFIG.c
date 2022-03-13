#include "TIMER_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Set the prescaler TIMx_PSC 
void TIMER6_PSC_90(void){		
	
	TIM6->PSC = (90 - 1);
}

// Set the ARR TIMx_ARR
void TIMER6_ARR_MAX(void){		
	
	TIM6->ARR = 0xffff;
}

// Enable the Timer and wait for update flag to ready TIMx_CR1
void Enable_TIMER6(void){		

	TIM6->CR1 |= TIM_CR1_CEN;
	
	// Wait for the update flag UIF to set in TIM6_SR
	while(!(TIM6->SR & (1<<0)));
}

// Set precise Delay
void TIMER6_Delay_us(uint16_t timeMicroSec){	
	
	// Reset the counter
	TIM6->CNT = 0;
	
	// wait for the counter to reach the given timer delay value
	// Each count of the timer takes exactly 1us as the timer clock is 1MHZ
	while(TIM6->CNT < timeMicroSec);
}
void TIMER6_Delay_ms(uint16_t timeMilliSec){	
	
	for(int i=0; i<timeMilliSec; i++)
		TIMER6_Delay_us(1000);							
}
void TIMER6_Delay_s(uint16_t timeSec){					
	
	for(int i=0; i<timeSec; i++)
		TIMER6_Delay_ms(1000);								
}

