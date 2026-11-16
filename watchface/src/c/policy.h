#pragma once
#include <stdbool.h>
static inline bool uses_24(int mode,bool watch24){return mode==2 || (mode==0 && watch24);}
static inline int display_hour(int hour,int mode,bool watch24){return uses_24(mode,watch24)?hour:(hour%12?hour%12:12);}
static inline int battery_bars(int percent){return (percent+24)/25;}
static inline int minute_progress(int minute){return 36*minute/59;}
