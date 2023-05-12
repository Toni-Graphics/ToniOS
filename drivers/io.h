#include <stdint.h>

#ifndef _IO_H
#define _IO_H

unsigned char inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
unsigned short inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
void wait_for_io(uint32_t timer_count);
void sleep(uint32_t timer_count);

#endif