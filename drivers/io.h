#include <stdint.h>

#ifndef _IO_H
#define _IO_H

unsigned char inb(uint16_t port);
void outb(uint16_t port, uint8_t data);

unsigned short inw(uint16_t port);
void outw(uint16_t port, uint16_t data);

void outsw(unsigned short port, const unsigned short *source, unsigned int count);
void insw(unsigned short port, unsigned short *destination, unsigned int count);


#endif