#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <stdio.h>
#include <stdlib.h>

#define MINUS 0x80000000
#define SCALE 0xFF0000

typedef struct {
  int bits[4];
} s21_decimal;

/*

bits[3] x0000000 xxxxxxxx 00000000 00000000
bits[2] 00000000 00000000 00000000 00000000
bits[1] 00000000 00000000 00000000 00000000
bits[0] 00000000 00000000 00000000 00000000
        127                               96
        95                                64
        63                                32
        31                                0
*/

typedef struct {
  int bits[8];
} s21_big_decimal;

#endif