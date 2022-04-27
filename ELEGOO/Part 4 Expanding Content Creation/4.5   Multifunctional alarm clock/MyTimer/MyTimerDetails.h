#ifndef MYTIMERDETAILS_H
#define MYTIMERDETAILS_H


#define BUTTON_MS_WAS_PRESSED_AND_LASTS_FOR_1000_MS (!digitalRead(BUTTON_MS) &&  1000 < (abs(time_button_ms-time_timer)))
#define BUTTON_S_WAS_PRESSED_AND_LASTS_FOR_1000_MS (!digitalRead(BUTTON_S) &&  1000 < (abs(time_button_s-time_timer)))

#define ELIMINAT_THE_JITTER_OF_BUTTON_S (200 < (abs(time_button_s - last_time_button_s)))
#define ELIMINAT_THE_JITTER_OF_BUTTON_MS (200 < (abs(time_button_ms - last_time_button_ms)))
#define ELIMINAT_THE_JITTER_OF_BUTTON_CHOOSE (200 < (abs(time_button_choose - last_time_button_choose)))
#define ELIMINAT_THE_JITTER_OF_BUTTON_DISPLAY_CHANGE (200 < (abs(time_button_display_change - last_time_button_display_change)))







#endif
