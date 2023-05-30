#include <stdint.h>

#ifndef _IO_H
#define _IO_H

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);

uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);

uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t data);

void outsw(unsigned short port, const unsigned short *source, unsigned int count);
void insw(unsigned short port, unsigned short *destination, unsigned int count);


#endif