/* EXAMPLE FROM https://stackoverflow.com/questions/21834403/how-to-display-time-on-stm32-discovery
Will have to tweak for our board.
This is how to get/set time from the real time clock (RTC) on board the STM Board. */




#define SENSOR_ADDRESS 0xD0 // or set this according to your HW configuration

#define HEX_2_DEC(val) (((val)>>5)*10+((val)%16))   //bit shift by 5 is equal to divide by 16
#define DEC_2_HEX(val) (((val)/10)*16+((val)%10))

typedef struct
{
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char weekday;
    unsigned char day;
    unsigned char month;
    unsigned char year;
}
raw_data_t;

void rtc_get(rtc_data_t* rtc_data)
{
    raw_data_t raw_data;
    i2c_polling_read(SENSOR_ADDRESS,0x00,sizeof(raw_data),(char*)&raw_data);
    rtc_data->second = HEX_2_DEC(raw_data.second);
    rtc_data->minute = HEX_2_DEC(raw_data.minute);
    rtc_data->hour   = HEX_2_DEC(raw_data.hour  );
    rtc_data->day    = HEX_2_DEC(raw_data.day   );
    rtc_data->month  = HEX_2_DEC(raw_data.month );
    rtc_data->year   = HEX_2_DEC(raw_data.year  );
}

void rtc_set(rtc_data_t* rtc_data)
{
    raw_data_t raw_data;
    raw_data.second = DEC_2_HEX(rtc_data->second);
    raw_data.minute = DEC_2_HEX(rtc_data->minute);
    raw_data.hour   = DEC_2_HEX(rtc_data->hour  );
    raw_data.day    = DEC_2_HEX(rtc_data->day   );
    raw_data.month  = DEC_2_HEX(rtc_data->month );
    raw_data.year   = DEC_2_HEX(rtc_data->year  );
    raw_data.weekday = RTC_Weekday_Monday; // or calculate the exact day
    i2c_polling_write(SENSOR_ADDRESS,0x00,sizeof(raw_data),(char*)&raw_data);
}






void rtc_init()
{
    RTC_InitTypeDef RTC_InitStructure;
    RTC_TimeTypeDef RTC_TimeStruct;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset RTC Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

    /* Enable the LSE OSC */
    RCC_LSEConfig(RCC_LSE_ON);

    /* Wait until LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);

    /* Set the time to 00h 00mn 00s AM */
    RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
    RTC_TimeStruct.RTC_Hours   = 0x00;
    RTC_TimeStruct.RTC_Minutes = 0x00;
    RTC_TimeStruct.RTC_Seconds = 0x00;
    RTC_SetTime(RTC_Format_BCD,&RTC_TimeStruct);
}
