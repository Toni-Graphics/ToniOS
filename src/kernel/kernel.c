#include <drivers/Vga/vga.h>
#include <drivers/Keyboard/keyboard.h>
#include <stdint.h>

void startShell() {
    for (;;) {
        printf("default@Boot: ")
        char* str = read_input(256);
        printf("\n")
    }
}

void kmain() {
    cls();
    printf("ToniOS Version 0.0.0.0.1 F\n");
    printf("Start shell\n");
    startShell();
}