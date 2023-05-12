#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef _STDIO_H
#define _STDIO_H

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

void printf_unsigned(unsigned long long number, int radix);
void printf_signed(long long number, int radix);
void printf(char* format, ...);

#endif