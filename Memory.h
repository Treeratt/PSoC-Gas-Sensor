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
//#include <project.h>
#include "project.h"
//#include "Memory.h"
#include "stdio.h"
#if !defined(MEMORY_FUNCTIONS_H)
#define MEMORY_FUNCTIONS_H

#include <project.h>
#include "cytypes.h"
#include "globals.h"
//#include "DAC.h"
    



#define R0_MQ_2_ADDRESS         0
#define R0_MQ_7_ADDRESS         2
#define R0_MQ_131_ADDRESS       4
#define R0_MQ_135_ADDRESS       6


/***************************************
*        Variables
***************************************/     
    
extern uint8 selected_voltage_source;
    
    
/***************************************
*        Function Prototypes
***************************************/ 

void Memory_Writebyte_EEPROM(uint16 data, uint16 address);
uint16 Memory_Readbyte_EEPROM(uint16 address);


#endif

/* [] END OF FILE */
