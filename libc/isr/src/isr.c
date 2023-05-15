#include <isr/include/isr.h>
#include <x86/x86.h>
#include <isr/include/idt.h>
#include <stdint.h>

struct idt_entry idt[256];

void isr_install() {
    for (int i=0; i < 256;i++) {
        register_isr(i, isr_handler);
    }

    struct {
        unsigned short limit;
        void* base;
    } __attribute__((packed)) idt_ptr = {
        .limit = sizeof(idt) - 1,
        .base = idt
    };
    asm volatile("lidt %0" : : "m"(idt_ptr));

    sti();
}

void isr_handler(int i_nr){
    printf("Interrupt number: %d\n", i_nr);
}

void register_isr(int interrupt_number, void (*handler)())
{
    uint32_t handler_address = (uint32_t)handler;
    idt[interrupt_number].offset_low = handler_address & 0xFFFF;
    idt[interrupt_number].selector = 0x08; // GDT code segment selector
    idt[interrupt_number].zero = 0;
    idt[interrupt_number].type_attr = 0x8E; // 32-bit interrupt gate
    idt[interrupt_number].offset_high = (handler_address >> 16) & 0xFFFF;
}
