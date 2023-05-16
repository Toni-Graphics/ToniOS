#include <stdio.h>
#include <multiboot.h>
#include <isr/isr.h>
#include <gdt/gdt.h>
#include <x86/x86.h>


void kmain(multiboot_info_t* mbi) {
    cls();

    printf("[INFO] installing GDT\n");

    gdt_install();

    printf("[INFO] installed  GDT\n"); 

    register_isr(0x80, isr_handler);

    printf("[INFO] installing ISR\n");
    isr_install();

    printf("[INFO] installed ISR\n");

    sti();

    asm volatile("int $0x80");
}
