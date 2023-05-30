#include <sys.h>
#include <drivers/io.h>
#include <stdio.h>

void execb(void* adr){
     
     __asm__("call %0" :: "m" (adr));
}

void io_wait() {
    asm volatile("jmp 1f\n\t"
                 "1:jmp 2f\n\t"
                 "2:");
}

// Function to perform shutdown
void shutdown() {
    outb(PM_COMMAND, PM_CMD_SHUTDOWN);
    io_wait();
}

// Function to perform reboot
void reboot() {
    outb(PM_COMMAND, PM_CMD_REBOOT);
    io_wait();
}