#include <stdio.h>
#include <stdlib.h>

struct CPU{
    using BYTE=unsigned char;
    using WORD=unsigned short;

    WORD PC;
    WORD SP;
    BYTE A, X, Y;
    BYTE C : 1;
    BYTE Z: 1;
    BYTE I: 1;
    BYTE D: 1;
    BYTE B: 1;
    BYTE O: 1;
    BYTE N: 1;
}