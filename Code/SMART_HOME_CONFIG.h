#include "USART_CONFIG.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

/**********************************

	Author : Umaar Abdullah Morshed
	Roll   : 09
	School : University of Dhaka
	Email  : umaarabdullah-2018525304@cs.du.ac.bd
	
**********************************/

/***
		Contains Subroutines which implements the functionalities of a Smart Home Configuration
***/

// Config Data Structure to store initial configuration
struct Config{
	int temp;
	int water;
	int humidity;
	int light;

};

// parse the initial configuration string and extract the field values and returns a Config Data with corresponding field values
struct Config parseInitConfig(unsigned char * configString);

// FLAG Functions
bool readConfigFlag(unsigned char * configString);		
bool readConfigAllFlag(unsigned char * configString);	

// Write Config parsing
void parseWriteConfig(unsigned char * configString, struct Config *configPtr);		

// Read Config parsing
void parseReadConfig(unsigned char * configString, struct Config configLocal);		
void parseReadAllConfig(struct Config configLocal); 		

// Temperature Control
void SMART_HOME_TEMP_CONTROL(void);

// Humidity Control
void SMART_HOME_HUMIDITY_CONTROL(void);

// Water Control
void SMART_HOME_WATER_CONTROL(void);

// Room Light Control
void SMART_HOME_LIGHT_CONTROL(void);

// SMART HOME CONTROL SYSTEM
void SMART_HOME_CONTROL_SYSTEM(struct Config *mainConfig);
