#include "RCC_CLOCK_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Select Mode As Alternate function in the MODER REGISTER GPIOx_MODER
void GPIOA_PA2_AF_Mode(void);		
void GPIOA_PA3_AF_Mode(void);		

// Select Mode as OUTPUT MODE in the GPIOx_MODER
// GPIOA
void GPIOA_PA7_OUTPUT_MODE(void);	
void GPIOA_PA9_OUTPUT_MODE(void);	
void GPIOA_PA10_OUTPUT_MODE(void);	
// GPIOB
void GPIOB_PB3_OUTPUT_MODE(void);	
void GPIOB_PB4_OUTPUT_MODE(void);	
void GPIOB_PB5_OUTPUT_MODE(void);	
void GPIOB_PB6_OUTPUT_MODE(void);	
void GPIOB_PB10_OUTPUT_MODE(void);
// GPIOC
void GPIOC_PC7_OUTPUT_MODE(void);

// Select Alternate function in the ALTERNATE FUNCTION LOW/HIGH REGISTER GPIOx_AFRL/GPIOx_AFRH
void GPIOA_PA2_AF7_USART2(void);
void GPIOA_PA3_AF7_USART2(void);

// Select Output Speed in the OUTPUT SPEED REGISTER GPIOx_OSPEEDR 
void GPIOA_PA2_Output_Speed_HIGH(void);		
void GPIOA_PA3_Output_Speed_HIGH(void);		
