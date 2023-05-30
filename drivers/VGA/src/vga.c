#include <vga.h>

#include <stdint.h>
#include <stdbool.h>
#include <drivers/io.h>
#include <string.h>

uint16_t linePosition = 0;
uint16_t line = 0;


void set_cursor(int offset) {
    offset /= 2;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = inb(VGA_DATA_REGISTER) << 8;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += inb(VGA_DATA_REGISTER);
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
    memcpy(
            (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < 40; col++) {
        set_char_at_video_memory(' ', 0, get_offset(col, MAX_ROWS - 1));
    }

    return offset - (2 * MAX_COLS);
}

int offset = 0;

uint16_t defaultColor = White;

void print(const char* string, uint16_t color) {
    int i = 0;
    while (string[i] != 0) {
        putChar(string[i], color);
        i++;
    }
    set_cursor(offset);
}

void putChar(char ch, uint16_t color) {
    if (offset >= MAX_ROWS * 40 * 2) {
        offset = scroll_ln(offset);
    }
    if (ch == '\n') {
        offset = move_offset_to_new_line(offset);
    } else if (ch == '\t') {
        offset += 8;
    } else if (ch == '\b') {
        offset -= 2;
    } else {
        set_char_at_video_memory(ch, color, offset);
        offset += 2;
    }
    
    set_cursor(offset);
}

void setColor(uint16_t color) {
    defaultColor = color;
}

uint16_t getColor() {
    return defaultColor;
}

void printBack() {
    putChar('\b', defaultColor);
    putChar(' ', defaultColor);
    putChar('\b', defaultColor);
}