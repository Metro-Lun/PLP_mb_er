#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    
    char c = CHAR_MAX;
    signed char sc = SCHAR_MIN;
    unsigned char uc = UCHAR_MAX;
    printf("char : %c\n", c);
    printf("signed char : %c\n", sc);
    printf("unsigned char : %c\n", uc);

    short s = SHRT_MIN;
    unsigned short us = USHRT_MAX;
    printf("short : %hd\n", s);
    printf("unsigned short : %hu\n", us);

    int i = INT_MAX;
    unsigned int ui = UINT_MAX;
    printf("int: %d\n", i);
    printf("unsigned int : %u\n", ui);

    long l = LONG_MAX;
    unsigned long ul = ULONG_MAX;
    long long ll = LLONG_MIN;
    unsigned long long  ull = ULLONG_MAX;
    printf("long int : %ld\n", l);
    printf("unsigned long : %lu\n", ul);
    printf("long long : %lld\n", ll);
    printf("unsigned long long, %llu\n", ull);

    float f_min = FLT_MIN;
    float f_max = FLT_MAX;
    double d_min = DBL_MIN;
    double d_max = DBL_MAX;
    printf("float minimum : %f\n", f_min);
    printf("float maximum : %f\n", f_max);
    printf("double minimum : %lf\n", d_min);
    printf("double maximum : %lf\n", d_max);

    return 0;
}