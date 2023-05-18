#include <stdio.h>
#include <multiboot.h>
#include <isr/isr.h>
#include <gdt/gdt.h>
#include <x86/x86.h>
#include <key.h>
#include <syscall/syscall.h>


void kmain(multiboot_info_t* mbi) {
    cls();

    gdt_install();

    printf("[OK] installed  GDT\n"); 

    register_isr(0x80, syscall_handler_driver);
    register_isr(0x21, syscall_handler);

    isr_install();

    printf("[OK] installed ISR\n");

}
