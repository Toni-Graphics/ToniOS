#include <kernel/kernel.h>

void kmain(multiboot_info_t* mbi) {
    ata_init();
    cls();

    FILE f = open(0, "abc");
    
    char* str = "Hi, thats here is a test str.\n";

    printf("Content to write: %s\n", str);

    printf("Writing ...\n");

    write(f, str);

    printf("Reading ...\n");

    char* buf;
    read(f, &buf);

    printf("Readed value: %s\n", buf);
}
