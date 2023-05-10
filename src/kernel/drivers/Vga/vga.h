#ifndef _VGA_H
#define _VGA_H

#include <nouse.h>

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <drivers/io.h>

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

    return offset - 2 * 40;
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
    } else {
        set_char_at_video_memory(ch, color, offset);
        offset += 2;
    }
    
    set_cursor(offset);
}

void NewLine() {
    print("\n", defaultColor);
}

uint32_t *get_vga_fb(void) {
    // Set up the registers for the VGA BIOS call
    uint16_t *bios = (uint16_t *)0xC0000000;
    bios[0x0416/2] = 0x0010;
    bios[0x0418/2] = 0x0003;

    // Call the VGA BIOS to get the framebuffer address
    uint16_t *addr = (uint16_t *)0x00000400;
    uint32_t *fb = (uint32_t *)(addr[0] << 12);

    return fb;
}



//Code from https://github.com/dedsylva/OS/tree/main
#define PRINTF_STATE_NORMAL         0
#define PRINTF_STATE_LENGTH         1
#define PRINTF_STATE_LENGTH_SHORT   2
#define PRINTF_STATE_LENGTH_LONG    3
#define PRINTF_STATE_SPEC           4

#define PRINTF_LENGTH_DEFAULT       0
#define PRINTF_LENGTH_SHORT_SHORT   1
#define PRINTF_LENGTH_SHORT         2
#define PRINTF_LENGTH_LONG          3
#define PRINTF_LENGTH_LONG_LONG     4

const char g_HexChars[] = "0123456789abcdef";

void printf_unsigned(unsigned long long number, int radix)
{
    char buffer[32];
    int pos = 0;

    // convert number to ASCII
    do 
    {
        unsigned long long rem = number % radix;
        number /= radix;
        buffer[pos++] = g_HexChars[rem];
    } while (number > 0);

    // print number in reverse order
    while (--pos >= 0)
        putChar(buffer[pos], White);
}

void printf_signed(long long number, int radix)
{
    if (number < 0)
    {
        putChar('-', White);
        printf_unsigned(-number, radix);
    }
    else printf_unsigned(number, radix);
}

void printf(char* format, ...) {
    va_list args;
    va_start(args, format);

    int state = PRINTF_STATE_NORMAL;
    int length = PRINTF_LENGTH_DEFAULT;
    int radix = 10;
    bool sign = false;
    bool number = false;

    while (*format)
    {
        switch (state)
        {
            case PRINTF_STATE_NORMAL:
                switch (*format)
                {
                    case '%':   state = PRINTF_STATE_LENGTH;
                                break;
                    default:    putChar(*format, White);
                                break;
                }
                break;

            case PRINTF_STATE_LENGTH:
                switch (*format)
                {
                    case 'h':   length = PRINTF_LENGTH_SHORT;
                                state = PRINTF_STATE_LENGTH_SHORT;
                                break;
                    case 'l':   length = PRINTF_LENGTH_LONG;
                                state = PRINTF_STATE_LENGTH_LONG;
                                break;
                    default:    goto PRINTF_STATE_SPEC_;
                }
                break;

            case PRINTF_STATE_LENGTH_SHORT:
                if (*format == 'h')
                {
                    length = PRINTF_LENGTH_SHORT_SHORT;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_LENGTH_LONG:
                if (*format == 'l')
                {
                    length = PRINTF_LENGTH_LONG_LONG;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_SPEC:
            PRINTF_STATE_SPEC_:
                switch (*format)
                {
                    case 'c':   putChar((char)va_arg(args, int), White);
                                break;

                    case 's':   
                                print(va_arg(args, const char*), White);
                                break;

                    case '%':   putChar('%', White);
                                break;

                    case 'd':
                    case 'i':   radix = 10; sign = true; number = true;
                                break;

                    case 'u':   radix = 10; sign = false; number = true;
                                break;

                    case 'X':
                    case 'x':
                    case 'p':   radix = 16; sign = false; number = true;
                                break;

                    case 'o':   radix = 8; sign = false; number = true;
                                break;

                    // ignore invalid spec
                    default:    break;
                }

                if (number)
                {
                    if (sign)
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     printf_signed(va_arg(args, int), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG:        printf_signed(va_arg(args, long), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG_LONG:   printf_signed(va_arg(args, long long), radix);
                                                        break;
                        }
                    }
                    else
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     printf_unsigned(va_arg(args, unsigned int), radix);
                                                        break;
                                                        
                        case PRINTF_LENGTH_LONG:        printf_unsigned(va_arg(args, unsigned  long), radix);
                                                        break;

                        case PRINTF_LENGTH_LONG_LONG:   printf_unsigned(va_arg(args, unsigned  long long), radix);
                                                        break;
                        }
                    }
                }

                // reset state
                state = PRINTF_STATE_NORMAL;
                length = PRINTF_LENGTH_DEFAULT;
                radix = 10;
                sign = false;
                break;
        }

        format++;
    }

    va_end(args);
}


void printBack() {  
    offset -= 2;
    print(" ", White);
    offset -= 2;
    set_cursor(offset);
}

#endif