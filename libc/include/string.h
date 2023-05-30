#include <stddef.h>

#ifndef _STRING_H
#define _STRING_H

size_t strlen(const char* str);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
char* strcat(char* d, const char* s);
char* strcpy(char* d, const char* s);
int strcmp(const char *s1, const char *s2);
char *strstr(char*s1, const char *s2);
char *strchr(const char *s, int c);
int strncmp(char* s1, const char* s2, size_t n);
char *ctos(const char c);
int isSupper(char c);
int isLower(char c);
int isAlpha(char c);
int isSpace(char c);
int isDigit(char c);
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
void memcpy(char *source, char *dest, int nbytes);

#endif