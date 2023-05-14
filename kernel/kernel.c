#include <stdio.h>
#include <vga.h>
#include <key.h>

void kmain() {
    cls();
    printf("ToniOS v0.0.3\n");

    while (1) {
        char* in = read_input(100);
        
        printf("\n");
        printf(in);
        printf("\n>");
    }
}