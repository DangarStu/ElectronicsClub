#ifndef KEY_H
#define KEY_H

int time_button_choose=0;
int last_time_button_choose=0;

#define ELIMINAT_THE_JITTER_OF_BUTTON_CHOOSE (200 < (abs(time_button_choose - last_time_button_choose)))

#endif
