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

#include "project.h"
#include "Memory.h"
#include "stdio.h"
//#include "helper_functions.h"



union DataUnion {
  uint8  byte_data[2];
  uint16 data;
} data_union;


void Memory_Writebyte_EEPROM(uint16 data, uint16 address) {
    EEPROM_Start();
    CyDelayUs(10);
    data_union.data = data;
    uint8 status = EEPROM_UpdateTemperature();
    status = EEPROM_WriteByte(data_union.byte_data[0], address);
    status = EEPROM_WriteByte(data_union.byte_data[1], address+1);
    EEPROM_Stop();
}
uint16 Memory_Readbyte_EEPROM(uint16 address) {
    EEPROM_Start();
    CyDelayUs(10);
    uint8 status = EEPROM_UpdateTemperature();
    CyDelayUs(10);
    data_union.byte_data[0] = EEPROM_ReadByte(address);
    data_union.byte_data[1] = EEPROM_ReadByte(address+1);
    EEPROM_Stop();
    return data_union.data;
}


