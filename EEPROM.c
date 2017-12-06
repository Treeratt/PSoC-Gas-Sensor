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
#include "EEPROM.h"


void Writebyte_EEPROM(uint8 data, uint16 address) {
    EEPROM_Start();
    CyDelayUs(10);
    uint8 blank_hold2 = EEPROM_UpdateTemperature();
    blank_hold2 = EEPROM_WriteByte(data, address);
    EEPROM_Stop();
}
uint8 helper_Readbyte_EEPROM(uint16 address) {
    EEPROM_Start();
    CyDelayUs(10);
    uint8 blank_hold2 = EEPROM_UpdateTemperature();
    CyDelayUs(10);
    uint8 hold = EEPROM_ReadByte(address);
    EEPROM_Stop();
    return hold;
}


