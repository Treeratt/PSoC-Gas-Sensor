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
#define RTC_SECONDS           0x80
#define RTC_MINUTES           0x82
#define RTC_HOURS             0x84
#define RTC_DATE              0x86
#define RTC_MONTH             0x88
#define RTC_DAY               0x8A
#define RTC_YEAR              0x8C
#define RTC_ENABLE            0x8E
#define RTC_TRICKLE           0x90

void RTC_Start(void);
void RTC_Stop(void);


/* [] END OF FILE */
