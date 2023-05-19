#include <syscall/syscall.h>
#include <register/reg.h>
#include <stdio.h>

void syscall_handler_driver(void) { //driver syscall
    registers *regs;
    getRegs(regs);
    printf("register rax 0x%x", regs->rax);
}
void syscall_handler(void) { // Normal syscall
    registers regs;
    getRegs(&regs);
}