#include <drivers/io.h>
#include <isr/isr.h>

#ifndef _TIMER_H
#define _TIMER_H

void timer_handler(void);
void timer_phase(int hz);

void timer_install();

void sleep(int ticks);

#endif