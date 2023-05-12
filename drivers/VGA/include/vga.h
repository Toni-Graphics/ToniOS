#include <stdint.h>
#include <stdbool.h>
#include <io.h>

#ifndef _VGA_H
#define _VGA_H


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

void set_cursor(int offset);
int get_cursur();

int get_row_from_offset(int offset);
int get_offset(int col, int row);
int move_offset_to_new_line(int offset);

void set_char_at_video_memory(char character, uint16_t color,int offset);

void print(const char* string, uint16_t color);
void putChar(char ch, uint16_t color);

void cls();

int scroll_ln(int offset);

#endif