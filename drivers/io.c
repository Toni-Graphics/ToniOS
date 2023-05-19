#include <io.h>
#include <stdint.h>

unsigned char inb(uint16_t port) {
    unsigned char result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short inw(uint16_t port) {
    unsigned short result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void outw(uint16_t port, uint16_t data) {
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}

void outsw(unsigned short port, const unsigned short *source, unsigned int count) {
    asm volatile("cld\n\t"
                 "rep outsw"
                 : "+S" (source), "+c" (count)
                 : "d" (port));
}

void insw(unsigned short port, unsigned short *destination, unsigned int count) {
    asm volatile("cld\n\t"
                 "rep insw"
                 : "+D" (destination), "+c" (count)
                 : "d" (port)
                 : "memory");
}

void memcpy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}