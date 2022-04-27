#ifndef MYTIMER_H
#define MYTIMER_H

void time_out();

static int time_button_ms=0;
static int time_button_s=0;
static int time_button_choose=0;

static int time_timer=0;

static int last_time_button_ms=0;
static int last_time_button_s=0;
static int last_time_button_choose=0;

static uint16_t flag_begin=0;

static uint16_t number=0;

const static uint8_t num_buf[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

#define BUTTON_S A3
#define BUTTON_MS 6    
#define BUTTON_CHOOSE A1

#define COM4 5
#define COM3 4
#define COM2 3
#define COM1 2

#define LATCH 12  
#define CLOCK 13 
#define DATA 8   

#define LED A0
#define BUZZER A2

#endif
