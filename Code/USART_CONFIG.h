#include "TIMER_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Enable USARTx
void USART2_Enable(void);		

// Program the M bit in USARTx_CR1 to define the word length
void USART2_Word_Length_8(void);		

// Select the desired baud rate using the baud rate register USARTx_BRR
void USART2_Baud_Rate_115200(void);		

// Enable USARTx Transmitter
void USART2_Enable_TE(void);		

// Enable USARTx Receiver
void USART2_Enable_RE(void);		

// Transmission
void UART2_SendChar(uint8_t byteData);				
void UART2_SendString(uint8_t *stringData);		

// Reception
uint8_t UART2_ReceiveChar(void);				
void UART2_ReceiveString(uint8_t *stringData);	

// Enable Receive RXNE interrupt 
void USART2_Enable_RECEIVE_INTERRUPT_RXNEIE(void);	

// Enable Transmission TXEIE interrupt 
void USART2_Enable_TRANSMIT_INTERRUPT_TXEIE(void);	

// Enable Transmission TCIE interrupt 
void USART2_Enable_TRANSMIT_COMPLETE_INTERRUPT_TCIE(void);		

