#include <stdio.h>
#include <key.h>
#include <stdint.h>
#include <string.h>

void kmain() {
    cls();
    printf("ToniOS Version 0.0.0.0.1 F\n");
    printf("Start shell\n");
    
    for (;;) {
        printf(">");
        read_input(100);
        printf("\n");
    }

}