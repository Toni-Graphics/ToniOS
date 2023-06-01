#include <kernel/kernel.h>

void kmain(multiboot_info_t* mbi) {
    ata_init();
    cls();

    DIR dir = mkdir("test", "/");

    DIR_ENTRY* entrys = getFiles(&dir);
    for (size_t i=0; i < (sizeof(entrys) / sizeof(DIR_ENTRY)); i++) {
        DIR_ENTRY entry = entrys[i];
        printf("Name %s, startBlock nr 0x%x, type: %d\n", entry.name, entry.startBlockNr, entry.type);
    }
}
