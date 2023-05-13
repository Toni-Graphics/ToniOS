#include <stddef.h>
#include <stdint.h>

#ifndef _MATH_H
#define _MATH_H

#define PI = 3.14159265358979323846264338327950288

double      sqrt(double x);
float       sqrtf(float x);
long double sqrtl(long double x);

double      pow(double x, double y);
float       powf(float x, float y);
long double powl(long double x, long double y);

double min(double x, double y);
double max(double x, double y);

double abs(double x);

unsigned long long fact(unsigned int n);

#endif