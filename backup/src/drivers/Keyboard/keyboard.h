#include <drivers/io.h>
#include <drivers/Vga/vga.h>
#include <string.h>
#include <stdbool.h>

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define NO 0

char* normal_codes[256] = {
  "ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", 
  "-", "=", "BACKSPACE", "\t", "q", "w", "e", "r", "t", "y", "u", 
  "i", "o", "p", "[", "]", "ENTER", "CTRL", "a", "s", "d", "f", 
  "g", "h", "j", "k", "l", ";", "'", "`", "LEFT_SHIFT", "\\", "z", "x", 
  "c", "v", "b", "n", "m", ",", ".", "/", "RIGHT_SHIFT", "*", "LEFT_ALT", 
  " ", "CAPS_LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", 
  "F9", "F10", "NUM_LOCK", "SCROLL_LOCK", "7", "8", "9", "-", "4", "5", 
  "6", "+", "1", "2", "3", "0", ".", "ERROR", "ERROR", "F11", "F12", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "CTRL", 
  "/", "PRT_SCR", "RIGHT_ALT", "ERROR", "HOME", "UP_ARROW", "PAGE_UP", 
  "LEFT_ARROW", "RIGHT_ARROW", "END", "DOWN_ARROW", "PAGE_DOWN", "INSERT", 
  "DELETE", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
  "ERROR", "PAUSE"
};

char* shiftcodes[256] = {
  "ERROR", "ESC", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", 
  "BACKSPACE", "\t", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}",
   "ENTER", "CTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", 
   "~", "LEFT_SHIFT", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", 
   "RIGHT_SHIFT", "*", "LEFT_ALT", " ", "CAPS_LOCK", "F1", "F2", "F3", "F4", 
   "F5", "F6", "F7", "F8", "F9", "F10", "NUM_LOCK", "SCROLL_LOCK", "7", "8", "9", 
   "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "ERROR", "ERROR", "F11", 
   "F12", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "CTRL", "/", "PRT_SCR", 
   "RIGHT_ALT", "ERROR", "HOME", "UP_ARROW", "PAGE_UP", "LEFT_ARROW", "RIGHT_ARROW", 
   "END", "DOWN_ARROW", "PAGE_DOWN", "INSERT", "DELETE", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", 
   "ERROR", "ERROR", "ERROR", "ERROR", "PAUSE"
};


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

bool CAPSLOCK = false;
bool SHIFT = false;

char* read_input(const size_t LEN) {
    char input[LEN];
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
            input[i] = '\0';
            break;
        } else if (char_str == "BACKSPACE" || char_str == "DEL") {
            // Backspace key
            if (i > 0) {
                i--;
                printBack();
            }
        } else if (char_str == "LEFT_SHIFT" || char_str == "RIGHT_SHIFT") {
            SHIFT = true;
        } else if (char_str == "CAPS_LOCK") {
            CAPSLOCK = !CAPSLOCK;
        } else if (char_str == "ESC" || char_str == "CTRL" || char_str == "HOME" || char_str == "NUM_LOCK") {}
         else if (scancode >= 0 && scancode < 256) {
            // Regular key
            if (char_str != "ERROR") {
                input[i] = char_str[0];
                i++;
                print(char_str, White);
                SHIFT = false;
            }
        }

        if (i >= LEN) {
            print("Input too long.\n", White);
        }
    }

    return input;
}


#endif