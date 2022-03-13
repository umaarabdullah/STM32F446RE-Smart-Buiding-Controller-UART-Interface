#include "stm32f446xx.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0

// Configure System Clock Using External Crystal as HSE and PLL as clock source
void SysClockConfig(void);

// Enable CLocks for GPIOx Ports
void GPIOA_CLOCK_ENABLE(void);		
void GPIOB_CLOCK_ENABLE(void);		
void GPIOC_CLOCK_ENABLE(void);		
void GPIOD_CLOCK_ENABLE(void);		
void GPIOE_CLOCK_ENABLE(void);		
void GPIOF_CLOCK_ENABLE(void);		
void GPIOG_CLOCK_ENABLE(void);		
void GPIOH_CLOCK_ENABLE(void);		

// Enable Clocks for USARTx
void USART2_CLOCK_ENABLE(void);		

// Enable Timer Clock
void TIM6_CLOCK_ENABLE(void);		
