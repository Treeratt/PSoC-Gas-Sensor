/*******************************************************************************
* File Name: MQ_7.c
* Version 1.0
*
* Description:
*  This file provides source code for using SEEED Studio's Air Quality Sensor v1.3 API.
*
* Note:
*   Need to have an ADC called ADC in topdesign
********************************************************************************
* Copyright 2017, Naresuan University.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/* [] END OF FILE */
#include "AirQuality.h"


/*******************************************************************************
* Function Name: init_sensor
********************************************************************************
*
* Summary:
*  
*
*
* Return:
*  LCD_initVar - global variable.
*
*******************************************************************************/

void init_sensor(void) {
    ADC_Start();  // start adc
    ADC_StartConvert();  // start it converting
}

/*******************************************************************************
* Function Name: get_pollution_level
********************************************************************************
*
* Summary:
*  
*
*
* Return:
*  uint16 adc counts: correlate with level of pollution.
*
*******************************************************************************/

uint16 get_pollution_level(void) {
    return ADC_GetResult16();
}



