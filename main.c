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
#include "MQ_2.h"
#include "MQ_7.h"
#include "MQ_135.h"
#include "MQ_131.h"
#include "stdio.h"
#include "stdbool.h"
#include "DHT11.h"
#include "usb_protocols.h"
#include "globals.h"
#include "math.h"
#include "Memory.h"
#include "ESP8266.h"
#include <device.h>




#include "Data_and_Func.h"
int uart_test();

//#define SSID  "Treerat"
//#define PASS  "027e3261f5b44c70a0d0f292182fddcf"
//const char* host = "wifitest.adafruit.com";

uint8 usb_data = 0;
uint8 count = 0;
char LCD_str[40];
uint8 OUT_buffer[20];
uint8 IN_buffer[20];
uint16 R0_s[nuber_sensors];

//void AirQualityairqualitysensor;
int current_quality = -1;

extern uint8 temperature;
extern uint8 humidity;
extern uint8 DHT_bytes[5];

CY_ISR_PROTO(DMA_Done);

SensorData all_data;
int i;

typedef struct {
    float32 b;
    float32 m;
} curve_params;

curve_params MQ135_params = { 5.12176, -0.3504 };
curve_params MQ7_params = { 25, -0.6987 };
curve_params MQ2_params = {25.98171445, -0.5038592728 };
curve_params MQ131_params = {0.4676658646, 0.3714570137};

typedef struct {
    uint16 MQ_2;
    uint16 MQ_7;
    uint16 MQ_131;
    uint16 MQ_135;
} SENSORS;

SENSORS R0s;

#define MQ_2_calibration_factor             0.1
#define MQ_7_calibration_factor             0.357
#define MQ_131_calibration_factor           1
#define MQ_135_calibration_factor           1.67

uint16 read_air_sensor(uint8 sensor_channel);
uint16 get_R(uint8 sensor_channel);
float32 get_ppm(uint16 sensor_channel, float32 R0s, curve_params sensor);
void calibrate_sensors(void);
float32 ppm;
bool calibrate_flag = true;
void run_single_read(void);
bool single_read_flag = false;
bool Power_MQ_131_flag = true;
void display_data(void);
void  power_all_sensors(void);
void  power_off_all_sensors(void);


CY_ISR(isr_cal_btn_Handler){
    Pin_SW2_ClearInterrupt();
    MQ_131_Power_Write( ~MQ_131_Power_Read() );
    Pin_SW2_ClearInterrupt();
    
    MQ_2_Power_Write( ~MQ_2_Power_Read() );
    
    MQ_135_Power_Write( ~MQ_135_Power_Read() );
    
    MQ_7_Power_Write( ~MQ_7_Power_Read() );
    //calibrate_sensors();
   // LCD_Position(0,0);
   // LCD_PrintString("Calibrated");
    calibrate_flag = true;

}
CY_ISR(isr_single_read_Handler){
//    LCD_Position(1,0);
//    LCD_PrintString("Run Single Read");
    single_read_flag = true;
}

CY_ISR(isr_timer_Handler){
    single_read_flag = true;
    Timer_read_ReadStatusRegister();
}

//CY_ISR( isr_Power_MQ_131 ) {
//    MQ_131_Power_Write( ~MQ_131_Power_Read() );
//    Pin_SW2_ClearInterrupt();
//    
//    MQ_2_Power_Write( ~MQ_2_Power_Read() );
//    
//    MQ_135_Power_Write( ~MQ_135_Power_Read() );
//    
//    MQ_7_Power_Write( ~MQ_7_Power_Read() );
//}

int main(void) {
    //int16_t get_pollution_level[nuber_sensors]; 
    isr_read_StartEx(isr_timer_Handler);
    isr_DHT_DONE_StartEx(DMA_Done);
    isr_cal_btn_StartEx(isr_cal_btn_Handler);
    //isr_cal_btn_StartEx( isr_Power_MQ_131 );
    isr_single_read_StartEx(isr_single_read_Handler);
    
    CyGlobalIntEnable;
 
    USBFS_Start(0, USBFS_DWR_VDDD_OPERATION);  // ให้ USB ทำงาน //initialize the USB
    USBFS_SetPowerStatus(USBFS_DEVICE_STATUS_SELF_POWERED);
    while(!USBFS_bGetConfiguration());  //รอUSB ได้รับค่าจากPC//Wait till it the usb gets its configuration from the PC
    USBFS_EnableOutEP(OUT_ENDPOINT); // ส่งค่าออก
  
    dma_config();
    LCD_Start();
    LCD_ClearDisplay();
    ADC_Start();
    AMux_Start();
    EEPROM_Start(); 
    
    //UART_Start();


    CyDelay(1000);
    
//    float32 R0_MQ135 = 1.67*get_R(0);
//    float32 R0_AirQuality = 1*get_R(1);
//    float32 R0_MQ7 = 0.357*get_R(2);
//    float32 R0_MQ2 =0.1*get_R(3);
//    float32 R0_MQ131 = 1*get_R(4);
    
    single_read_flag = false;
    LCD_ClearDisplay();
//    LCD_Position(1,0);
//    LCD_PrintString("Start");
    DHTread();
    for(;;) {
        
         uint8 input = USB_CheckInput(OUT_buffer);
        
        if(USBFS_IsConfigurationChanged()) {  // if the configuration is changed reenable the OUT ENDPOINT
            while(!USBFS_GetConfiguration()) {  // wait for the configuration with windows / controller is updated
            }
            USBFS_EnableOutEP(OUT_ENDPOINT);  // reenable OUT ENDPOINT
        }

        if ( input == true ){
            LCD_Position(1,0);
            LCD_PrintString("got in");
            switch( OUT_buffer[0] ) {
            case 'O':;  
                calibrate_sensors();
                break;
            case 'T':;
                single_read_flag = true;
                run_single_read();
                break;
            case 'P':;
                Timer_read_Stop();
               // single_read_flag = false;
                break;
            case 'R' :;
                Timer_read_Start();
                break;
            case 'N' :;
                power_all_sensors();
                break;
            case 'F' :;
                power_off_all_sensors();
               
                break;
                
            }
            OUT_buffer[0] = 0;
        }  
        
        if (calibrate_flag){
            calibrate_sensors();
            calibrate_flag = false;
        }
        if (single_read_flag) {
            
            run_single_read();
            USB_Export_Data(all_data, 18);
            CyDelay(10);
            single_read_flag = false;
            //display_data();  
  
        }
        run_single_read();
        display_data();  
        //DHTread();
        CyDelay(500);
        all_data.humidity = DHT_bytes[0];  
        all_data.temperture = DHT_bytes[2];
//        LCD_Position(1,0);
//        sprintf(LCD_str, "t,h:%i|%i ", all_data.temperture,all_data.humidity);
//        LCD_PrintString(LCD_str);
//        sprintf(LCD_str, "count:%i ", count);
//        LCD_PrintString(LCD_str); 
//        count++;
    }          

}
uint16 read_air_sensor(uint8 sensor_channel) {
    AMux_Select(sensor_channel);
    CyDelay(100);
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);  
    return ADC_GetResult16();
}
uint16 get_R(uint8 sensor_channel) {
    uint16 adc_counts = read_air_sensor(sensor_channel);
    uint16 voltage = ADC_CountsTo_mVolts(adc_counts);  // USE TO CALCULATE R0 = 5V/Vm * Rl - Rl
    return ((5000.00/voltage) *1000.00 - 1000.00);  
}
float32 get_ppm(uint16 sensor_channel, float32 R0s, curve_params sensor){
    float32 y =( (float32) get_R(sensor_channel) / (float32) R0s);
    return pow( y/sensor.b, 1.0/sensor.m );
    //return  sensor.b*pow(y,sensor.m);
}
void calibrate_sensors(void) {
    // get R0 for all 4 sensors
    R0s.MQ_2 = MQ_2_calibration_factor*get_R(MQ_2_SENSOR_CHANNEL);
    R0s.MQ_135 = MQ_135_calibration_factor*get_R(MQ_135_SENSOR_CHANNEL);
    R0s.MQ_7 = MQ_7_calibration_factor*get_R(MQ_7_SENSOR_CHANNEL);
    R0s.MQ_131 = MQ_131_calibration_factor*get_R(MQ_131_SENSOR_CHANNEL);
    // save R0s to eeprom
    Memory_Writebyte_EEPROM(R0s.MQ_2, R0_MQ_2_ADDRESS);
    Memory_Writebyte_EEPROM(R0s.MQ_135, R0_MQ_135_ADDRESS);
    Memory_Writebyte_EEPROM(R0s.MQ_7, R0_MQ_7_ADDRESS);
    Memory_Writebyte_EEPROM(R0s.MQ_131, R0_MQ_131_ADDRESS);
}

void run_single_read(void){
    all_data.MQ_135 = get_ppm(0,R0s.MQ_135,MQ135_params);
    all_data.MQ_7 = get_ppm(2,R0s.MQ_7,MQ7_params);
    all_data.MQ_2 = get_ppm(3,R0s.MQ_2,MQ2_params);
    all_data.MQ_131 = get_ppm(4,R0s.MQ_131,MQ131_params);
}

void display_data(void) {
    LCD_Position(0,0);
    sprintf(LCD_str, "MQ_2:%3.0f ppm",all_data.MQ_2);
    LCD_PrintString(LCD_str);
    LCD_Position(1,0);
    sprintf(LCD_str, "MQ_7:%3.0f ppm",all_data.MQ_7);
    LCD_PrintString(LCD_str);
    CyDelay(500);
    LCD_Position(0,0);
    sprintf(LCD_str, "MQ_131:%3.0f ppm",all_data.MQ_131);
    LCD_PrintString(LCD_str);
    LCD_Position(1,0);
    sprintf(LCD_str, "MQ_135:%3.0f ppm",all_data.MQ_135);
    LCD_PrintString(LCD_str);
   // CyDelay(1000);
}

void power_all_sensors(void) {
    MQ_131_Power_Write( 1 );
    MQ_2_Power_Write( 1 );
    MQ_135_Power_Write( 1 );
    MQ_7_Power_Write( 1 ); 
}

void power_off_all_sensors(void) {
    MQ_131_Power_Write( 0 );
    MQ_2_Power_Write( 0 );
    MQ_135_Power_Write( 0 );
    MQ_7_Power_Write( 0 ); 
}
