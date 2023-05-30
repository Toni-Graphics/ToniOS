#include "x86.h"

void sti() {
    asm volatile("sti");
}

void cli() {
    asm volatile("cli");
}