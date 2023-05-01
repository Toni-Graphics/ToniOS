#ifndef _VGA_H
#define VGA_H

#include "stdint.h"
#include "io.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 40
#define MAX_COLS 80

uint16_t linePosition = 0;
uint16_t line = 0;

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

enum COLOR {
    Black        = 0x0,
    Blue         = 0x1,
    Green        = 0x2,
    Cyan         = 0x3,
    Red          = 0x4,
    Magenta      = 0x5,
    Brown        = 0x6,
    LightGray    = 0x7,
    DarkGray     = 0x8,
    LightBlue    = 0x9,
    LightGreen   = 0xA,
    LightCyan    = 0xB,
    LightRed     = 0xC,
    LightMagenta = 0xD,
    Yellow       = 0xE,
    White        = 0xF,

};

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);
    return offset * 2;
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0,get_row_from_offset(offset) + 1);
}

void set_char_at_video_memory(char character, uint16_t color,int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = color;
}

void cls() {
    uint16_t *buffer = (uint16_t*)0xB8000;
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        buffer[i] = 0;
    }
    set_cursor(get_offset(0, 0));
}

int scroll_ln(int offset) {
    memory_copy(
            (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < 40; col++) {
        set_char_at_video_memory(' ', 0, get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * 40;
}

int offset = 0;

uint16_t defaultColor = White;
void print(const char* string, uint16_t color) {
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * 40 * 2) {
            offset = scroll_ln(offset);
        }
        if (string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory(string[i], color, offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void NewLine() {
    print("\n", defaultColor);
}
#endif