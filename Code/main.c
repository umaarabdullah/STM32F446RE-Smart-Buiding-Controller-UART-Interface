#include "SMART_HOME_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

int main(){
	
	// Clock Configurations
	SysClockConfig();
	GPIOA_CLOCK_ENABLE();
	GPIOB_CLOCK_ENABLE();
	GPIOC_CLOCK_ENABLE();
	USART2_CLOCK_ENABLE();
	TIM6_CLOCK_ENABLE();
	
	// Configure GPIO Pins PA2 and PA3 as ALTERNATE FUNCTION and USART2 and OUTPUT SPEED HIGH
	// Alternate function mode Pins
	GPIOA_PA2_AF_Mode();
	GPIOA_PA3_AF_Mode();
	// Alternate Function Selection USART2
	GPIOA_PA2_AF7_USART2();
	GPIOA_PA3_AF7_USART2();
	GPIOA_PA2_Output_Speed_HIGH();
	GPIOA_PA3_Output_Speed_HIGH();
	// Output Mode Pins
	GPIOA_PA7_OUTPUT_MODE();
	GPIOA_PA9_OUTPUT_MODE();
	GPIOA_PA10_OUTPUT_MODE();
	GPIOB_PB3_OUTPUT_MODE();
	GPIOB_PB4_OUTPUT_MODE();
	GPIOB_PB5_OUTPUT_MODE();
	GPIOB_PB6_OUTPUT_MODE();
	GPIOB_PB10_OUTPUT_MODE();
	GPIOC_PC7_OUTPUT_MODE();
	
	// Configure Timer
	TIMER6_PSC_90();
	TIMER6_ARR_MAX();
	Enable_TIMER6();
	
	// Configure UART2 
	USART2_Enable();
	USART2_Word_Length_8();
	USART2_Baud_Rate_115200();
	USART2_Enable_TE();
	USART2_Enable_RE();
	
	uint8_t configString[100];									
	uint8_t configStringCopy[100];							
		
	// User must send a '.' character at the end of the command
	// Receive the Initial Config from the computer to MCU : VIA USART2 POLL METHOD
	UART2_ReceiveString(configString);
	strcpy(configStringCopy, configString);					
	struct Config mainConfig;
	mainConfig = parseInitConfig(configString);
	strcpy(configString, configStringCopy);					
	
	// Enable Reception Interrupt
	USART2_Enable_RECEIVE_INTERRUPT_RXNEIE();
	
	// Enable Tranmission Complete Interrupt
	USART2_Enable_TRANSMIT_COMPLETE_INTERRUPT_TCIE();
	
	NVIC_EnableIRQ(USART2_IRQn);
	
	while(1){
		
		SMART_HOME_CONTROL_SYSTEM(&mainConfig);				
		
	}
	
}





