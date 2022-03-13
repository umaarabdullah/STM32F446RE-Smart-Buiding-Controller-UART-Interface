#include "GPIO_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/


// GPIOx MODER REGISTER CONFIGURATION
// ALTERNATE FUNCTION MODES
void GPIOA_PA2_AF_Mode(){
	GPIOA->MODER |= GPIO_MODER_MODE2_1;		
}
void GPIOA_PA3_AF_Mode(){
	GPIOA->MODER |= GPIO_MODER_MODE3_1;		
}
// Select Mode as OUTPUT MODE in the GPIOx_MODER
// GPIOA
void GPIOA_PA7_OUTPUT_MODE(void){		
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
}
void GPIOA_PA9_OUTPUT_MODE(void){		
	GPIOA->MODER |= GPIO_MODER_MODER9_0;
}
void GPIOA_PA10_OUTPUT_MODE(void){	
	GPIOA->MODER |= GPIO_MODER_MODER10_0;
}
// GPIOB
void GPIOB_PB3_OUTPUT_MODE(void){	
	GPIOB->MODER |= GPIO_MODER_MODE3_0;		
	GPIOB->MODER &= ~(1<<7);				
}
void GPIOB_PB4_OUTPUT_MODE(void){		
	GPIOB->MODER |= GPIO_MODER_MODE4_0;	
	GPIOB->MODER &= ~(1<<9);			
}
void GPIOB_PB5_OUTPUT_MODE(void){		
	GPIOB->MODER |= GPIO_MODER_MODE5_0;	
	GPIOB->MODER &= ~(1<<11);							
}
void GPIOB_PB6_OUTPUT_MODE(void){		
	GPIOB->MODER |= GPIO_MODER_MODE6_0;
}
void GPIOB_PB10_OUTPUT_MODE(void){	
	GPIOB->MODER |= GPIO_MODER_MODE10_0;
}
// GPIOC
void GPIOC_PC7_OUTPUT_MODE(void){	
	GPIOC->MODER |= GPIO_MODER_MODE7_0;
}


// Select Alternate function in the ALTERNATE FUNCTION LOW/HIGH REGISTER GPIOx_AFRL/GPIOx_AFRH
void GPIOA_PA2_AF7_USART2(){
	GPIOA->AFR[0] |= (7 << 8);		
}
void GPIOA_PA3_AF7_USART2(){
	GPIOA->AFR[0] |= (7 << 12);		
}


// Select Output Speed in the OUTPUT SPEED REGISTER GPIOx_OSPEEDR 
void GPIOA_PA2_Output_Speed_HIGH(){	
	GPIOA->OSPEEDR |= (3 << 4);		
}
void GPIOA_PA3_Output_Speed_HIGH(){
	GPIOA->OSPEEDR |= (3 << 6);		
}
