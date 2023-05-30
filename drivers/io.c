#include <io.h>
#include <stdint.h>

uint8_t inb(uint16_t port) {
    unsigned char result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t inw(uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void outw(uint16_t port, uint16_t data) {
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}

uint32_t inl(uint16_t port) {
    uint32_t value;
    asm volatile("inl %1, %0" : "=a"(value) : "dN"(port));
    return value;
}
void outl(uint16_t port, uint32_t data) {
    asm volatile("outl %0, %1" : : "a"(data), "dN"(port));
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