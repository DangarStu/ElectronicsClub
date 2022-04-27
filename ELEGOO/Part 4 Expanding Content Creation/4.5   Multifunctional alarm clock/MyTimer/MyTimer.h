 #ifndef MYTIMER_H
#define MYTIMER_H
#include <dht_nonblocking.h>
#include <EEPROM.h>

void time_out();
void clock_to_timer();
unsigned int eeprom_read_int(unsigned int address);

volatile static uint8_t waiting_time_cnt=0;

volatile static int time_button_ms=0;
volatile static int time_button_s=0;
volatile static int time_button_choose=0;
volatile static int time_button_display_change=0;

volatile static int time_timer=0;

volatile static int last_time_button_ms=0;
volatile static int last_time_button_s=0;
volatile static int last_time_button_choose=0;
volatile static int last_time_button_display_change=0;

volatile static uint8_t function_clock=1;
volatile static uint16_t flag_begin=0;
volatile static uint16_t flag_year=0;
volatile static uint16_t flag_month=0;
volatile static uint16_t flag_temperature=0;
volatile static uint16_t flag_humidity=0;
volatile static uint16_t flag_alarm=1;
volatile static uint16_t flag_alarm_set=0;
volatile static uint16_t flag_alarm_set_ok= EEPROM.read(3);
volatile static uint16_t flag_alarm_ring=0;
volatile static uint16_t flag_100ms_update_clock=1;

volatile static float temperature;
volatile static float humidity;

volatile static uint8_t  press_cnt;

volatile static uint16_t number=0;

volatile const static uint8_t num_buf[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x39,0x76};
volatile const static uint8_t num_buf_1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x39,0x76};//.

volatile static uint8_t dht11_buf[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
volatile static uint8_t dht11_buf2[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};

volatile static uint16_t alarm_value = eeprom_read_int(0);


#define DHT_SENSOR_PIN 11
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_TYPE_11 );

#define TIMER_TIME 50

#define BUTTON_S A0
#define BUTTON_MS A2    
#define BUTTON_CHOOSE A1
#define BUTTON_DISPLAY_CHANGE 10

//#define COM4 5
//#define COM3 4
//#define COM2 30
//#define COM1 2                        

#define COM1 2
#define COM2 4
#define COM3 A3
#define COM4 7

#define LATCH 12  //STCP
#define CLOCK 13 //SHCP
#define DATA 8   //DS

#define BUZZER 3


#define GREEN 9
#define RED 6

static const uint8_t rgb_color_delay = 15; 
static uint16_t task1_cnt=0;
static uint16_t task2_cnt=0;
static uint16_t task3_cnt=0;

enum display_mode
{
  DISPLAY_YEAR,
  DISPLAY_MONTH,
  DISPLAY_TIME,
  DISPLAY_TEMPERATURE,
  DISPLAY_HUNMIDITY,
};


#endif
