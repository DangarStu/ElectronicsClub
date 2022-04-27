#ifndef CLOCK_H
#define CLOCK_H

#include <Wire.h>

struct RTCDateTime
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t dayOfWeek;
    uint32_t unixtime;
};

RTCDateTime dt;
static uint8_t error_cnt;

#define DS3231_ADDRESS              (0x68)

#define DS3231_REG_TIME             (0x00)
#define DS3231_REG_CONTROL          (0x0E)

const uint8_t daysArray [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const uint8_t dowArray[] PROGMEM = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };


#endif
