/*******************************************************************************
* File Name: MQ_2.c
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

#ifndef AIRQUALITY_H
#define AIRQUALITY_H
    
#include <project.h>    
#include "MQ_2.h"
 
/***************************************
*        Function Prototypes
***************************************/
    
void init_sensor(void);    
uint16 get_pollution_level(void);
    
#endif

/* [] END OF FILE */




