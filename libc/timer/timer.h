#include <drivers/io.h>
#include <isr/isr.h>
#include <stdio.h>

#ifndef _TIMER_H
#define _TIMER_H

void timer_handler(void);
void timer_phase(int hz);

void timer_install();

int sleep(int ticks);

#endif