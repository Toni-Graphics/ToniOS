#include <string.h>
#include <stdio.h>
#include <vga.h>
#include <keys.h>
#include <key.h>

bool CAPSLOCK = false;
bool SHIFT = false;

uint8_t keyscan() {
    unsigned char brk;
    static uint8_t key = 0;
    uint8_t scan = inb(0x60);
    brk = scan & 0x80;
    scan = scan & 0x7f;
    if (brk) 
        return key = 0;
    else if (scan != key) 
        return key = scan;
    else
        return 0;
}

char* in = "";

char* read_input(const size_t LEN) {
    memset(in, 0, strlen(in));
    
    int i = 0;

    while (true) {
        int scancode = keyscan();
        
        char* char_str;

        if (!SHIFT && !CAPSLOCK)
            char_str = normal_codes[scancode];
        else
            char_str = shiftcodes[scancode];

        if (char_str == "ENTER") {
            // Enter key
            strcat(in, "\0");
            break;
        } else if (char_str == "BACKSPACE" || char_str == "DEL") {
            // Backspace key
            if (i > 0) {
                i--;
                printBack();
                in[strlen(in)-1] = ' ';
            }
        } else if (char_str == "LEFT_SHIFT" || char_str == "RIGHT_SHIFT") {
            SHIFT = true;
        } else if (char_str == "CAPS_LOCK") {
            CAPSLOCK = !CAPSLOCK;
        } else if (char_str == "ESC" || char_str == "CTRL" || char_str == "HOME" || char_str == "NUM_LOCK") {}
         else if (scancode >= 0 && scancode < 256) {
            // Regular key
            if (char_str != "ERROR") {
                strcat(in, char_str);
                i++;
                printf(char_str);
                SHIFT = false;
            }
        }

        if (i >= LEN) {
            printf("Input too long.\n");
        }
    }

    return in;
}