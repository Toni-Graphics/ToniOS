#ifndef _STRING_H
#define _STRING_H

#include "stddef.h"
#include <drivers/io.h>

size_t strlen(const char* str) {
    size_t ret = 0;
    
    while (str[ret] != 0) 
        ret++;

    return ret;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
    const unsigned char* a = (const unsigned char*)aptr;
    const unsigned char* b = (const unsigned char*)bptr;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) 
            return -1;
        else if (b[i] < a[i])
            return 1;
        return 0;
    }
}

void* memset(void* bufptr, int value, size_t size) {
    unsigned char* buf = (unsigned char*)bufptr;

    for (size_t i = 0; i < size; i++)
        buf[i] = (unsigned char) value;
        
    return bufptr;
}


char* strcat(char* d, const char* s) {
    char* tmp = d;
    while(*d) d++;
    while((*d++ = *s++) != 0);
    return tmp;
}

char* strcpy(char* d, const char* s) {
    char* tmp = d;

    while ((*d++ = *s++) != 0);

    return tmp;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2) )
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *strstr(char*s1, const char *s2) {
    size_t n = strlen(s2);
    while(*s1)
        if (!memcmp(s1++, s2, n))
            return s1-1;
    return 0;
}

char *strchr(const char *s, int c) {
    while (*s != (char) c ) {
        if (!*s++)
            return 0;
    }
    return (char *)s;
}

int strncmp(char* s1, const char* s2, size_t n) {
    while (n--)
        if(*s1++ != *s2++)
            return *(unsigned char*)(s1 - s2) - *(unsigned char*)(s2-s1);
}

char *ctos(const char c) {
    char s[2];
    s[0] = c;
    s[1] = '\0';
    return s;
}

int isSupper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

int isAlpha(char c) {
    return isLower(c) || isSupper(c);
}

int isSpace(char c) {
    return (c == '\0' || c == '\t' || c == '\n' || c == '\12');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

char *ltrim(char *s) {
    while(isSpace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char* back = s + strlen(s);
    while (isSpace(*--back));
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s));
}

#endif