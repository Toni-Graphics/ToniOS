#include <register/reg.h>

void initRegs(registers *regs) {
    regs->rax = 0;
    regs->rbx = 0;
    regs->rcx = 0;
    regs->rdx = 0;
    regs->rsi = 0;
    regs->rdi = 0;
    regs->rsp = 0;
    regs->rbp = 0;

    regs->eax = 0;
    regs->ebx = 0;
    regs->ecx = 0;
    regs->edx = 0;
    regs->esi = 0;
    regs->edi = 0;
    regs->esp = 0;
    regs->ebp = 0;

    regs->ax = 0;
    regs->bx = 0;
    regs->cx = 0;
    regs->dx = 0;
    regs->si = 0;
    regs->di = 0;
    regs->sp = 0;
    regs->bp = 0;

    regs->ah = 0;
    regs->bh = 0;
    regs->ch = 0;
    regs->dh = 0;
    regs->al = 0;
    regs->bl = 0;
    regs->cl = 0;
    regs->dl = 0;
    regs->sil = 0;
    regs->dil = 0;
    regs->spl = 0;
    regs->bpl = 0;
}

void getRegs(registers *regs) {

    initRegs(regs);

    /*asm volatile(
        "mov %%rax, %0\n\t"
        "mov %%rbx, %1\n\t"
        "mov %%rcx, %2\n\t"
        "mov %%rdx, %3\n\t"
        "mov %%rsi, %4\n\t"
        "mov %%rdi, %5\n\t"
        "mov %%rsp, %6\n\t"
        "mov %%rbp, %7\n\t"
        :
        : "m"(regs->rax), "m"(regs->rbx), "m"(regs->rcx), "m"(regs->rdx),
          "m"(regs->rsi), "m"(regs->rdi), "m"(regs->rsp), "m"(regs->rbp)
        :
    );

    asm volatile(
        "mov %%eax, %0\n\t"
        "mov %%ebx, %1\n\t"
        "mov %%ecx, %2\n\t"
        "mov %%edx, %3\n\t"
        "mov %%esi, %4\n\t"
        "mov %%edi, %5\n\t"
        "mov %%esp, %6\n\t"
        "mov %%ebp, %7\n\t"
        :
        : "m"(regs->eax), "m"(regs->ebx), "m"(regs->ecx), "m"(regs->edx),
          "m"(regs->esi), "m"(regs->edi), "m"(regs->esp), "m"(regs->ebp)
        :
    );

    asm volatile(
        "mov %%ax, %0\n\t"
        "mov %%bx, %1\n\t"
        "mov %%cx, %2\n\t"
        "mov %%dx, %3\n\t"
        "mov %%si, %4\n\t"
        "mov %%di, %5\n\t"
        "mov %%sp, %6\n\t"
        "mov %%bp, %7\n\t"
        :
        : "m"(regs->ax), "m"(regs->bx), "m"(regs->cx), "m"(regs->dx),
          "m"(regs->si), "m"(regs->di), "m"(regs->sp), "m"(regs->bp)
        :
    );

    asm volatile(
        "mov %%ah, %0\n\t"
        "mov %%bh, %1\n\t"
        "mov %%ch, %2\n\t"
        "mov %%dh, %3\n\t"
        "mov %%al, %4\n\t"
        "mov %%bl, %5\n\t"
        "mov %%cl, %6\n\t"
        "mov %%dl, %7\n\t"
        "mov %%sil, %8\n\t"
        "mov %%dil, %9\n\t"
        "mov %%spl, %10\n\t"
        "mov %%bpl, %11\n\t"
        :
        : "m"(regs->ah), "m"(regs->bh), "m"(regs->ch), "m"(regs->dh),
          "m"(regs->al), "m"(regs->bl), "m"(regs->cl), "m"(regs->dl),
          "m"(regs->sil), "m"(regs->dil), "m"(regs->spl), "m"(regs->bpl)
        :
    );*/
}