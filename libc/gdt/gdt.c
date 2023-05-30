#include <gdt/gdt.h>

struct gdt_entry gdt[3];  // Assuming three segments in this example
struct gdt_ptr gdtr;

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    // Set up the descriptor base address
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // Set up the descriptor limits
    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;

    // Set up the granularity and access flags
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install() {
    gdtr.base  = (uint32_t)&gdt;
    gdtr.limit = sizeof(gdt) - 1;

    gdt_set_gate(0, 0, 0, 0, 0);

    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);


    asm volatile("lgdt %0" : : "m"(gdtr));

    asm volatile(
        "movw $0x10, %ax\n\t"
        "movw %ax, %ds\n\t"
        "movw %ax, %es\n\t"
        "movw %ax, %fs\n\t"
        "movw %ax, %gs\n\t"
        "movw %ax, %ss\n\t"
        "ljmp $0x08, $flush\n\t"
        "flush: nop"
    );

}
