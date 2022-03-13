#include "SMART_HOME_CONFIG.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

struct Config config;												
struct Config *configMainPointer;						
uint8_t bufferRXConfigString[100];					
int bufferRXConfigStringIndex;						
uint8_t readConfigBuffer[100];						
uint8_t *readConfig = readConfigBuffer;			

// Interrupt Service Routine
void USART2_IRQHandler(void){
	
	unsigned int statusRegister;
	statusRegister = USART2->SR;
	
	if(statusRegister & USART_SR_RXNE){			
			
		uint8_t byteData = USART2->DR;			
		USART2->SR &= ~(USART_SR_RXNE);			
		
		if(byteData != '.'){					
			
			bufferRXConfigString[bufferRXConfigStringIndex++] = byteData;		
		}
		else{																	
			
			// put null terminator '\0'
			bufferRXConfigString[bufferRXConfigStringIndex] = '\0';	
			
			// reinitialize the global variable bufferConfigStringIndex
			bufferRXConfigStringIndex = 0;
			
			// SEND received config string for parsing
			uint8_t configString[100];
			strcpy(configString, bufferRXConfigString);				
			
			if(readConfigFlag(configString)){						
				strcpy(configString, bufferRXConfigString);			
				if(readConfigAllFlag(configString)){				
						strcpy(configString, bufferRXConfigString);	
						parseReadAllConfig(config); 				
				}
				else{												
					strcpy(configString, bufferRXConfigString);		
					parseReadConfig(configString, config);			
				}
				// transmit the readConfigBuffer string to the computer from MCU
				UART2_SendString(readConfig);
			}
			else{														
				strcpy(configString, bufferRXConfigString);				
				parseWriteConfig(configString, configMainPointer);		
				config = *configMainPointer;							
			}
		}
		
	}
	else if(statusRegister & USART_SR_TC){					
		// transmission complete
		USART2->SR &= ~(USART_SR_TC);					
	}
	
}

// parse the initial configuration string and extract the field values and returns a Config Data with corresponding field values
struct Config parseInitConfig(unsigned char * configString){
	
	struct Config initConfig;
	
	// flags
	bool tempFlag = false;
	bool waterFlag= false;
	bool humidityFlag= false;
	bool lightFlag= false;
	
	// split the string into tokens after each space " "
	unsigned char * token = strtok(configString, " ");
	while( token != NULL ) {
      
			// if any iteration sets the flag then we store the next iteration value and reset the flag
			if(tempFlag){
				tempFlag = false;
				initConfig.temp = atoi(token);		
			}
			else if(waterFlag){
				waterFlag = false;
				initConfig.water = atoi(token);		
			}
			else if(humidityFlag){
				humidityFlag = false;
				initConfig.humidity = atoi(token);	
			}
			else if(lightFlag){
				lightFlag = false;
				initConfig.light = 0; 	
				// iterate over the light config and store the decimal equivalent of the 3bit binary input
				int numOfBitsLight = 4;	
				for(int i=0; i<numOfBitsLight; i++){
					if(*(token+i) == '1'){
						initConfig.light |= (1 << (numOfBitsLight-1 - i));	
					}						
					if(*(token+i) == '0'){
					// do nothing
					}
				}
			}
			
			// check for config labels and set the corresponding flag
			if(strcmp(token, "temp") == 0)
				tempFlag = true;
			else if(strcmp(token, "water") == 0)
				waterFlag = true;
			else if(strcmp(token, "hum") == 0)
				humidityFlag = true;
			else if(strcmp(token, "light") == 0)
				lightFlag = true;
			
      token = strtok(NULL, " ");
   }
	
	 return initConfig;
}

// FLAG Functions
// Will return TRUE if command is read config and FALSE if write config
bool readConfigFlag(unsigned char * configString){
	
	unsigned char *token;
	token = strtok(configString, " ");
	
	if(strcmp(token, "Read") == 0)
		return true;
	else 
		return false;
}
// will return TRUE if command is Read Config and FALSE if Read Config x
bool readConfigAllFlag(unsigned char * configString){
	
	if(strlen(configString) > 13)		
			return false;
	else 
			return true;
}

// Write Config parsing
// parse string and write the new config field value in the Config data type 
void parseWriteConfig(unsigned char * configString, struct Config *configPtr){
	
	unsigned char *token;
	token = strtok(configString, " ");
	token = strtok(NULL, " ");
	
	// compare the second token to ascertain which field has been provided
	if(strcmp(token, "temp") == 0){
		// get the next token which is the number field
		token = strtok(NULL, " ");
		configPtr->temp = atoi(token);
	}
	else if(strcmp(token, "water") == 0){
		// get the next token which is the number field
		token = strtok(NULL, " ");
		configPtr->water = atoi(token);
	}
	else if(strcmp(token, "hum") == 0){
		// get the next token which is the number field
		token = strtok(NULL, " ");
		configPtr->humidity = atoi(token);
	}
	else if(strcmp(token, "light") == 0){
		token = strtok(NULL, " ");		
		configPtr->light = 0; 	
		
		// iterate over the light config and store the decimal equivalent of the 3bit binary input
		int numOfBitsLight = 4;	
		for(int i=0; i<numOfBitsLight; i++){
			if(*(token+i) == '1'){
				configPtr->light |= (1 << (numOfBitsLight-1 - i));	
			}						
			if(*(token+i) == '0'){
				// do nothing
			}
		}
	}
	
}

// Read Config parsing
// will return the queried field value as a string 
void parseReadConfig(unsigned char * configString, struct Config configLocal){

	// clear the readConfigBuffer
	strcpy(readConfigBuffer, "");
	
	unsigned char *token = strtok(configString, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	
	// Compare the third token to ascertain which field has been provided 
	// Concatenate to form the resultant string
	if(strcmp(token, "temp") == 0){
		
		unsigned char *tempPiece = " temp : ";
		strcat(readConfigBuffer, tempPiece);
		unsigned char tempValue[3];
		sprintf(tempValue, "%d", configLocal.temp);
		strcat(readConfigBuffer, tempValue);
	}	
	else if(strcmp(token, "water") == 0){
		
		unsigned char *waterPiece = " water : ";
		strcat(readConfigBuffer, waterPiece);
		unsigned char waterValue[3];
		sprintf(waterValue, "%d", configLocal.water);
		strcat(readConfigBuffer, waterValue);
	}
	else if(strcmp(token, "hum") == 0){
		
		unsigned char *humPiece = " hum : ";
		strcat(readConfigBuffer, humPiece);
		unsigned char humValue[3];
		sprintf(humValue, "%d", configLocal.humidity);
		strcat(readConfigBuffer, humValue);
	}
	else if(strcmp(token, "light") == 0){
		
		unsigned char *lightPiece = " light : ";
		strcat(readConfigBuffer, lightPiece);
		unsigned char lightValue[5];
		int lightDecVal = configLocal.light;
		if(lightDecVal & (1 << 3))
			lightValue[0] = '1';
		else 
			lightValue[0] = '0';
		if(lightDecVal & (1 << 2))
			lightValue[1] = '1';
		else 
			lightValue[1] = '0';
		if(lightDecVal & (1 << 1))
			lightValue[2] = '1';
		else 
			lightValue[2] = '0';
		if(lightDecVal & (1 << 0))
			lightValue[3] = '1';
		else 
			lightValue[3] = '0';
		
		lightValue[4] = '\0';		// null terminator
		strcat(readConfigBuffer, lightValue);	
	}
	
}
// will return the whole config as a string 
void parseReadAllConfig(struct Config configLocal){
	
	// clear the readConfigBuffer
	strcpy(readConfigBuffer, "");
	
	// concatenate to form the resultant string 
	unsigned char *tempPiece = " temp : ";
	strcat(readConfigBuffer, tempPiece);
	unsigned char tempValue[3];
	sprintf(tempValue, "%d", configLocal.temp);
	strcat(readConfigBuffer, tempValue);
	
	unsigned char *waterPiece = " water : ";
	strcat(readConfigBuffer, waterPiece);
	unsigned char waterValue[3];
	sprintf(waterValue, "%d", configLocal.water);
	strcat(readConfigBuffer, waterValue);
	
	unsigned char *humPiece = " hum : ";
	strcat(readConfigBuffer, humPiece);
	unsigned char humValue[3];
	sprintf(humValue, "%d", configLocal.humidity);
	strcat(readConfigBuffer, humValue);
	
	unsigned char *lightPiece = " light : ";
	strcat(readConfigBuffer, lightPiece);
	unsigned char lightValue[5];
		int lightDecVal = configLocal.light;
		if(lightDecVal & (1 << 3))
			lightValue[0] = '1';
		else 
			lightValue[0] = '0';
		if(lightDecVal & (1 << 2))
			lightValue[1] = '1';
		else 
			lightValue[1] = '0';
		if(lightDecVal & (1 << 1))
			lightValue[2] = '1';
		else 
			lightValue[2] = '0';
		if(lightDecVal & (1 << 0))
			lightValue[3] = '1';
		else 
			lightValue[3] = '0';
		
	lightValue[4] = '\0';		
	strcat(readConfigBuffer, lightValue);
	
}

// Temperature Control
void SMART_HOME_TEMP_CONTROL(){	
	
	// if PC0 is 1
	if((GPIOC->IDR & (1<<0))){
		// if PC1 is 1
		if((GPIOC->IDR & (1<<1))){					
			// Set Pin PA10
			GPIOA->BSRR |= GPIO_BSRR_BS10;		
			TIMER6_Delay_s(30);					
			// Reset Pin PA10
			GPIOA->BSRR |= GPIO_BSRR_BR10;		
		}
		// else if PC1 is 0
		else {											
			// set Pin PB3
			GPIOB->BSRR |= GPIO_BSRR_BS3;			
			TIMER6_Delay_s(30);						
			// Reset Pin PB3
			GPIOB->BSRR |= GPIO_BSRR_BR3;			
		}
	}
	// else if PC0 is 0
	else{
		// if PC1 is 0
		if(!(GPIOC->IDR & (1<<1))){					
			// do nothing
		}
	}
	
}

// Humidity Control
void SMART_HOME_HUMIDITY_CONTROL(void){			
	
	// if PB0 is 1
	if((GPIOB->IDR & (1<<0))){
		// if PA4 is 1
		if((GPIOA->IDR & (1<<4))){					
			// Set PB4
			GPIOB->BSRR |= GPIO_BSRR_BS4;			
			TIMER6_Delay_s(10);						
			// Reset PB4
			GPIOB->BSRR |= GPIO_BSRR_BR4;			
		}
		// else if PA4 is 0
		else {										
			// Set PB5
			GPIOB->BSRR |= GPIO_BSRR_BS5;			
			TIMER6_Delay_s(10);						
			// Reset PB5
			GPIOB->BSRR |= GPIO_BSRR_BR5;			
		}
	}
	// else if PB0 is 0
	else{
		// if PA4 is 0
		if(!(GPIOA->IDR & (1<<4))){					
			// do nothing
		}
	}
	
}

// Water Control
void SMART_HOME_WATER_CONTROL(void){		
	
	// if PA1 is 1 meaning water level just below range
	if((GPIOA->IDR & (1<<1))){
		// Set PB10
		GPIOB->BSRR |= GPIO_BSRR_BS10;		
		TIMER6_Delay_s(7);					
		GPIOB->BSRR |= GPIO_BSRR_BR10;		
	}
	// else if PA1 is 0 meaning water level is atmost upper range and atleast lower range
	else{
		// do nothing
	}
}

// Room Light Control
// INPUT PINS PA5 PB9 PB8
// Input Conditions for Bulbs in Living (00), Dining (01), Bedroom (10), and office room (11)
// Configuration 0001 means will respond to office room only PA7 will be 1
// OUTPUT PINS PA9 PC7 PB6 PA7
void SMART_HOME_LIGHT_CONTROL(){		
	
	// Check DAY/NIGHT Sensor Input
	// If PA5 is 1 means NIGHT TIME
	if(GPIOA->IDR & (1<<5)){
		
		// Turn All lights On which were set to respond in the Config
		if(config.light & (1<<3)){			
			// Set PA9
			GPIOA->BSRR |= GPIO_BSRR_BS9;	
		}
		else{		
			GPIOA->BSRR |= GPIO_BSRR_BR9;	
		}
		if(config.light & (1<<2)){			
			// Set PC7
			GPIOC->BSRR |= GPIO_BSRR_BS7;
		}
		else{		
			GPIOC->BSRR |= GPIO_BSRR_BR7;
		}
		if(config.light & (1<<1)){			
			// Set PB6
			GPIOB->BSRR |= GPIO_BSRR_BS6;
		}
		else{		
			GPIOB->BSRR |= GPIO_BSRR_BR6;
		}
		if(config.light & (1<<0)){			
			// Set PA7
			GPIOA->BSRR |= GPIO_BSRR_BS7;
		}
		else{		
			GPIOA->BSRR |= GPIO_BSRR_BR7;
		}
	}
	// If PA5 is 0 means DAY TIME
	else{		
		
		// Turn All lights off which were set to respond in the Config
		if(config.light & (1<<3)){		
			// Reset PA9
			GPIOA->BSRR |= GPIO_BSRR_BR9;	
		}
		if(config.light & (1<<2)){		
			// Reset PC7
			GPIOC->BSRR |= GPIO_BSRR_BR7;
		}
		if(config.light & (1<<1)){		
			// Reset PB6
			GPIOB->BSRR |= GPIO_BSRR_BR6;
		}
		if(config.light & (1<<0)){		
			// Reset PA7
			GPIOA->BSRR |= GPIO_BSRR_BR7;
		}
	}
	
	// Check Luminosity Sensor Inputs of the different rooms
	// PB9 PB8
	// if 00 then turn living room light (PIN PA9) on if it was set to respond in the Config !
	if(!(GPIOB->IDR & (1<<9))){				
		if(!(GPIOB->IDR & (1<<8))){			
				if((config.light & (1<<3)))
					GPIOA->BSRR |= GPIO_BSRR_BS9;		
				else 
					GPIOA->BSRR |= GPIO_BSRR_BR9;		
		}
		else{											
			// if 01 then turn Dining room light (PIN PC7) on if it was set to respond in the Config !
			if((config.light & (1<<2)))
				GPIOC->BSRR |= GPIO_BSRR_BS7;		
			else 
				GPIOC->BSRR |= GPIO_BSRR_BR7;		
		}
	}
	else{											
		if(!(GPIOB->IDR & (1<<8))){					
			// if 10 then turn Bed room light (PIN PB6) on if it was set to respond in the Config !
			if((config.light & (1<<1)))
				GPIOB->BSRR |= GPIO_BSRR_BS6;		
			else 
				GPIOB->BSRR |= GPIO_BSRR_BR6;		
		}
		else{										
			// if 11 then turn Office room light (PIN PA7) on if it was set to respond in the Config !
			if((config.light & (1<<0)))
				GPIOA->BSRR |= GPIO_BSRR_BS7;		
			else 
				GPIOA->BSRR |= GPIO_BSRR_BR7;		
		}
	}
	
}

// SMART HOME CONTROL SYSTEM
void SMART_HOME_CONTROL_SYSTEM(struct Config *mainConfig){
	
	config = *mainConfig;
	configMainPointer = mainConfig;
	
	SMART_HOME_TEMP_CONTROL();
	SMART_HOME_HUMIDITY_CONTROL();
	SMART_HOME_WATER_CONTROL();
	SMART_HOME_LIGHT_CONTROL();
	
}






