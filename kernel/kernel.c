#include <stdio.h>
#include <multiboot.h>
#include <isr/include/isr.h>
#include <x86/x86.h>


void kmain(multiboot_info_t* mbi) {
    cls();


    printf("[INFO] installing ISR\n");
    isr_install();

    printf("[INFO] installed ISR");

    sti();

    asm volatile("int $0x13");
}
