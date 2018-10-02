/* EXAMPLE FROM https://stackoverflow.com/questions/21834403/how-to-display-time-on-stm32-discovery
Will have to tweak for our board.
This is how to get/set time from the real time clock (RTC) on board the STM Board. */

typedef struct
{
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned char year;
}
rtc_data_t;

void rtc_get(rtc_data_t* rtc_data);
void rtc_set(rtc_data_t* rtc_data);
void rtc_init(void);
