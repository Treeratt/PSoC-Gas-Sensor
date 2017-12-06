/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>  

char c;
int i=0;
char wifi_messages[100];
    
void GetText(void){	/******************************************************/			
    uint8 targetLen = strlen(wifi_messages); 		// The length of the search fragment
    uint8 index = 0;  								// maximum target string length is 255 bytes
    LCD_Position(0,0);
    while(UART_GetRxBufferSize()) {							
        c = UART_ReadRxData();   // read UART 
        LCD_PutChar(c);
        wifi_messages[i]=c;  // is the [index] element of the search string?
        i++;
    }
    
} 
//int connectWiFi(char *SSID, char *PASS){
//    char sendString[32];
//    UART_ClearRxBuffer(); 
//    sprintf(sendString,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID, PASS);	// form the string "AT + CWJAP =" SSID "," PASS "\ r \ n
//    UART_PutString(sendString); // send it to the module 
//    if (!WaitText("OK", 100))
//      return 0;	//0-для  прошивки 00160901	// команда получена, "OK"  но это не подтверждает подключение для прошивки   00160901	
//      CyDelay(5000);		 // 	для  прошивки 00160901			   	   даем время на подключение
//      UART_PutString("AT+CIFSR\r\n"); 	//для  прошивки 00160901	// Получить IP через 5 сек это будет подтверждением подключения
//    if(WaitText("ERROR", 500))
//      return 0;	// для  прошивки 00160901	// попытка не удалась.....
//      return 1;  //1-для  прошивки 00160901	
////     LCD_Position(1,1);
////     sprintf(connectWiFi,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID, PASS);
////     LCD_PrintString(connectWiFi);// признак успешного подключения к WIFI
//}
//     
//     
///* [] END OF FILE */
//