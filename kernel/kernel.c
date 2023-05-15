#include <stdio.h>
#include <vga.h>
#include <key.h>
#include <multiboot.h>


void kmain(multiboot_info_t* mbi) {
    cls();

    printf("ToniOS v0.0.3\n");

    printf("drives_length 0x%x", mbi->drives_length);

    for (;;);
}
