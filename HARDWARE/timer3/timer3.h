#ifndef _TIMER4_H
#define _TIMER4_H

#include <stdint.h>

void timer_init(uint32_t num_50us); //以50us为定时基本单位
void start_timer(void);
void stop_timer(void);

#endif
