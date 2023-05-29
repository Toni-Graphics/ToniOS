#include <syscall/syscall.h>
#include <register/reg.h>
#include <stdio.h>

void  syscall_handler_driver(void) { //driver syscall
    int register_value;
    
    asm("movl %%eax, %0" : "=r" (register_value));
    printf("register value: %d\n", register_value);
}

void syscall_handler(void) { // Normal syscall
    registers regs;
    getRegs(&regs);
}