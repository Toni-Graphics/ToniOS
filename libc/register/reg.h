#include <stdint.h>

#ifndef _REGISTER_H
#define _REGISTER_H

typedef struct {

    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rsp;
    uint64_t rbp;

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t esp;
    uint32_t ebp;

    uint16_t ax;
    uint16_t bx;
    uint16_t cx;
    uint16_t dx;
    uint16_t si;
    uint16_t di;
    uint16_t sp;
    uint16_t bp;

    uint8_t ah;
    uint8_t bh;
    uint8_t ch;
    uint8_t dh;
    uint8_t al;
    uint8_t bl;
    uint8_t cl;
    uint8_t dl;
    uint8_t sil;
    uint8_t dil;
    uint8_t spl;
    uint8_t bpl;

} registers;

void getRegs(registers *regs);

#endif