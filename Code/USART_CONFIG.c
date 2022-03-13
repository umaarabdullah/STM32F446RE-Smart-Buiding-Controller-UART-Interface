#include "USART_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

// Enable USARTx in CR1 Register
// Enable USART2
void USART2_Enable(){
	
	USART2->CR1 = 0x00;		
	USART2->CR1 |= USART_CR1_UE;	
}

// Program the M bit in USARTx_CR1 to define the word length
// Configure M bit in USART2_CR1
void USART2_Word_Length_8(void){
	
	USART2->CR1 &= ~(1 << 12);		
}

// Select the desired baud rate using the baud rate register USARTx_BRR
// Set Baud rate of USART2 to 115200
void USART2_Baud_Rate_115200(void){
	
	// set baud rate to 115200 by configuring the div and mantissa bits in the USART2_BRR 
	USART2->BRR |= (7 << 0);		
	USART2->BRR |= (24 << 4);		
}

// Enable USARTx Transmitter
void USART2_Enable_TE(void){
	
	USART2->CR1 |= USART_CR1_TE;		
}

// Enable USARTx Receiver
void USART2_Enable_RE(void){
	
	USART2->CR1 |= USART_CR1_RE;		
}

// Transmission
void UART2_SendChar(uint8_t byteData){
	
	// Transmit an unsigned char Character using USART2 port
	USART2->DR = byteData;
	
	while(!(USART2->SR & USART_SR_TC));
	
}
// Transmit a string using USART2 port in UART Communication mode
void UART2_SendString(uint8_t *stringData){
	
	while(*stringData)
		UART2_SendChar(*stringData++);
}

// Reception
// Receive an unsigned char character using USART2 port in UART POLL METHOD	
uint8_t UART2_ReceiveChar(void){
	
	// When the RXNE bit is set. It indicates data has been received and can be read
	while(!(USART2->SR & USART_SR_RXNE));
	
	uint8_t byteData = USART2->DR;
	
	return byteData;
}
// Recieve a string of characters until a (.) is detected UART POLL METHOD
void UART2_ReceiveString(uint8_t *stringData){
	
	uint8_t byteCharData;
	byteCharData = UART2_ReceiveChar();
	// recieve a character from UART2 port unitl a newline or carriage return character is detected
	// store the character in an array of characters i.e a string using it's base address pointer stringdata
	// '.' period character is used to detect input string end
	while(byteCharData != '.'){
		*(stringData++) = byteCharData;
		byteCharData = UART2_ReceiveChar();
	}
	*stringData = '\0';		
}

// Enable Receive RXNE interrupt 
void USART2_Enable_RECEIVE_INTERRUPT_RXNEIE(void){		
	
	USART2->CR1 |= USART_CR1_RXNEIE;
}

// Enable Transmission TXEIE interrupt 
void USART2_Enable_TRANSMIT_INTERRUPT_TXEIE(void){		
	
	USART2->CR1 |= USART_CR1_TXEIE;
}

// Enable Transmission TCIE interrupt

void USART2_Enable_TRANSMIT_COMPLETE_INTERRUPT_TCIE(void){		
	
	USART2->CR1 |= USART_CR1_TCIE;
}


