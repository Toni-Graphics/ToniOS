#include <math.h>

double sqrt(double x) {
    double guess = x / 2;
    double prevGuess;
    
    do {
        prevGuess = guess;
        guess = (prevGuess + x / prevGuess) / 2;
    } while (abs(guess - prevGuess) >= 0.0001);

    return guess;
}

float sqrtf(float x) {
    float guess = x / 2;
    double prevGuess;
    
    do {
        prevGuess = guess;
        guess = (prevGuess + x / prevGuess) / 2;
    } while (abs(guess - prevGuess) >= 0.0001);

    return guess;
}

long double sqrtl(long double x) {
    float guess = x / 2;
    double prevGuess;
    
    do {
        prevGuess = guess;
        guess = (prevGuess + x / prevGuess) / 2;
    } while (abs(guess - prevGuess) >= 0.0001);

    return guess;
}

double pow(double x, double y) {
    double result;
    for (double temp=0; temp < y; temp++) {
        result *= x;
    }
    return result;
}

float powf(float x, float y) {
    float result;
    for (double temp=0; temp < y; temp++) {
        result *= x;
    }
    return result;
}

long double powl(long double x, long double y) {
    long double result;
    for (double temp=0; temp < y; temp++) {
        result *= x;
    }
    return result;
}

double max(double x, double y) {
    return (x > y) ? x : y;
}

double min(double x, double y) {
    return (x < y) ? x : y;
}

double abs(double x) {
    return (x < 0) ? -x : x;
}

unsigned long long fact(unsigned int n) {
    unsigned long long result = 1;
    unsigned int i;
    
    for (i = 2; i <= n; i++) {
        result *= i;
    }
    
    return result;
}