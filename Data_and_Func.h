#include <project.h>
#include <stdio.h>   /* sprintf() */

uint8 Com_Data;         	// data in RX
uint8 recon;
char8 ch;       			//Data received from the Serial port  
uint8 count_RX=0;			// counter bytes of RX

//-----------------------------------------------------------------------------------
void Reset1(void);	
int connectWiFi(char *SSID, char *PASS);	
void http(char *output); 	
void webserver(void);	
uint16 WaitText(char *target, int time);
void IP_to_LCD(void);
void SetServer(int port);