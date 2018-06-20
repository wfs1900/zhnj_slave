#ifndef __RTC_H
#define __RTC_H
#include "sys.h"    
u8 RTC_Init(void);              //RTC初始化

void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec); //设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);             //周期性唤醒定时器设置

HAL_StatusTypeDef RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);      //RTC时间设置
HAL_StatusTypeDef RTC_Set_Date(u8 year,u8 month,u8 date,u8 week);	//RTC日期设置
HAL_StatusTypeDef RTC_GetTime(RTC_TimeTypeDef *RTC_TimeStruct);
HAL_StatusTypeDef RTC_GetDate(RTC_DateTypeDef *RTC_DateStruct);

struct tm {
    int tm_sec;     /* seconds after the minute [0-60] */
    int tm_min;     /* minutes after the hour [0-59] */
    int tm_hour;    /* hours since midnight [0-23] */
    int tm_mday;    /* day of the month [1-31] */
    int tm_mon;     /* months since January [0-11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday [0-6] */
    int tm_yday;    /* days since January 1 [0-365] */
    int tm_isdst;   /* Daylight Savings Time flag */
    long tm_gmtoff;  /* offset from CUT in seconds */
    char *tm_zone;   /* timezone abbreviation */
};
typedef long time_t;
time_t XTIME(time_t * timer);
struct tm* gmtime(const time_t* timer);
#endif
