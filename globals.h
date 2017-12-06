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
#if !defined(_GLOBALS_H)
#define _GLOBALS_H

#include <project.h>

//typedef struct  {
//    uint8 temperture;
//    uint8 humidity;
//    uint16 MQ_2;
//    uint16 MQ_7;
//    uint16 MQ_135;
//    uint16 MQ_131;
//
// } SensorData;

typedef struct  {
    float32 MQ_2;
    float32 MQ_7;
    float32 MQ_135;
    float32 MQ_131;
    uint8 temperture;
    uint8 humidity;

 } SensorData;

extern char wifi_messages[100];

#define nuber_sensors               4
#define MQ_2_SENSOR_CHANNEL         3
#define MQ_135_SENSOR_CHANNEL       0
#define MQ_7_SENSOR_CHANNEL         2
#define MQ_131_SENSOR_CHANNEL       4

#endif

/* [] END OF FILE */
