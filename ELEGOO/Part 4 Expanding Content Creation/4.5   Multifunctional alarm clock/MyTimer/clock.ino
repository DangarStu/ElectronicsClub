#include "clock.h"

void clock_init()
{
  clock_begin();
}

void update_clock()
{
  if(flag_100ms_update_clock)
    {dt = clock_getDateTime();}
}

bool clock_begin(void)
{
    Wire.begin();

    clock_setBattery(true, false);

    dt.year = 2000;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    dt.dayOfWeek = 6;
    dt.unixtime = 946681200;

    return true;
}

void clock_setBattery(bool timeBattery, bool squareBattery)
{
    uint8_t value;

    value = clock_readRegister8(DS3231_REG_CONTROL);

    if (squareBattery)
    {
        value |= 0b01000000;
    } else
    {
        value &= 0b10111111;
    }

    if (timeBattery)
    {
        value &= 0b01111011;
    } else
    {
        value |= 0b10000000;
    }

    clock_writeRegister8(DS3231_REG_CONTROL, value);
}

void clock_writeRegister8(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
        Wire.write(value);
    #else
        Wire.send(reg);
        Wire.send(value);
    #endif
    Wire.endTransmission();
}

RTCDateTime clock_getDateTime(void)
{
    int values[7];

    Wire.beginTransmission(DS3231_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(DS3231_REG_TIME);
    #else
        Wire.send(DS3231_REG_TIME);
    #endif
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDRESS, 7);

    while(!Wire.available()) 
  {
    delay(1); 
    error_cnt++;
    if(error_cnt>15)
    {
      error_cnt=0;
     return dt;}};

    for (int i = 6; i >= 0; i--)
    {
        #if ARDUINO >= 100
            values[i] = bcd2dec(Wire.read());
        #else
            values[i] = bcd2dec(Wire.receive());
        #endif
    }

    Wire.endTransmission();

    dt.year = values[0] + 2000;
    dt.month = values[1];
    dt.day = values[2];
    dt.dayOfWeek = values[3];
    dt.hour = values[4];
    dt.minute = values[5];
    dt.second = values[6];
    dt.unixtime = unixtime();

    return dt;
}

uint8_t clock_readRegister8(uint8_t reg)
{
    uint8_t value;
    Wire.beginTransmission(DS3231_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
    #else
        Wire.send(reg);
    #endif
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDRESS, 1);
    while(!Wire.available()) {
    delay(1); 
    error_cnt++;
    if(error_cnt>15)
    {
      error_cnt=0;
     return value;}};
    #if ARDUINO >= 100
        value = Wire.read();
    #else
        value = Wire.receive();
    #endif;
    Wire.endTransmission();

    return value;
}

uint8_t bcd2dec(uint8_t bcd)
{
    return ((bcd / 16) * 10) + (bcd % 16);
}

uint8_t dec2bcd(uint8_t dec)
{
    return ((dec / 10) * 16) + (dec % 10);
}

uint32_t unixtime(void)
{
    uint32_t u;

    u = time2long(date2days(dt.year, dt.month, dt.day), dt.hour, dt.minute, dt.second);
    u += 946681200;

    return u;
}

uint16_t date2days(uint16_t year, uint8_t month, uint8_t day)
{
    year = year - 2000;

    uint16_t days16 = day;

    for (uint8_t i = 1; i < month; ++i)
    {
        days16 += pgm_read_byte(daysArray + i - 1);
    }

    if ((month == 2) && isLeapYear(year))
    {
        ++days16;
    }

    return days16 + 365 * year + (year + 3) / 4 - 1;
}

long time2long(uint16_t days, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    return ((days * 24L + hours) * 60 + minutes) * 60 + seconds;
}

bool isLeapYear(uint16_t year)
{
    return (year % 4 == 0);
}

void clock_setDateTime(const char* date, const char* time)
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    year = conv2d(date + 9);

    switch (date[0])
    {
        case 'J': month = date[1] == 'a' ? 1 : month = date[2] == 'n' ? 6 : 7; break;
        case 'F': month = 2; break;
        case 'A': month = date[2] == 'r' ? 4 : 8; break;
        case 'M': month = date[2] == 'r' ? 3 : 5; break;
        case 'S': month = 9; break;
        case 'O': month = 10; break;
        case 'N': month = 11; break;
        case 'D': month = 12; break;
    }

    day = conv2d(date + 4);
    hour = conv2d(time);
    minute = conv2d(time + 3);
    second = conv2d(time + 6);

    setDateTime(year+2000, month, day, hour, minute, second);
}

uint8_t conv2d(const char* p)
{
    uint8_t v = 0;

    if ('0' <= *p && *p <= '9')
    {
        v = *p - '0';
    }

    return 10 * v + *++p - '0';
}

void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    Wire.beginTransmission(DS3231_ADDRESS);

    #if ARDUINO >= 100
        Wire.write(DS3231_REG_TIME);Serial.println("wwwwwwwwwwwww");
    #else
        Wire.send(DS3231_REG_TIME);Serial.println("bbbbbbbbbbb");
    #endif

    #if ARDUINO >= 100
        Wire.write(dec2bcd(second));
        Wire.write(dec2bcd(minute));
        Wire.write(dec2bcd(hour));
        Wire.write(dec2bcd(dow(year, month, day)));
        Wire.write(dec2bcd(day));
        Wire.write(dec2bcd(month));
        Wire.write(dec2bcd(year-2000));
    #else
        Wire.send(dec2bcd(second));
        Wire.send(dec2bcd(minute));
        Wire.send(dec2bcd(hour));
        Wire.send(dec2bcd(dow(year, month, day)));
        Wire.send(dec2bcd(day));
        Wire.send(dec2bcd(month));
        Wire.send(dec2bcd(year-2000));
    #endif

    #if ARDUINO >= 100
        Wire.write(DS3231_REG_TIME);
    #else
        Wire.send(DS3231_REG_TIME);
    #endif

    Wire.endTransmission();
}

uint8_t dow(uint16_t y, uint8_t m, uint8_t d)
{
    uint8_t dow;

    y -= m < 3;
    dow = ((y + y/4 - y/100 + y/400 + pgm_read_byte(dowArray+(m-1)) + d) % 7);

    if (dow == 0)
    {
        return 7;
    }

    return dow;
}
