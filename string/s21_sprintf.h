#ifndef SRC_HEADERS_S21_SPRINTF_H_
#define SRC_HEADERS_S21_SPRINTF_H_
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
typedef struct {
  char flag[10];
  int width;
  int accuracy;
  char type;
} spec;
char *s21_reverse(char *str);
int s21_sprintf(char *str, const char *format, ...);
int specifier(int x, const char *f, spec *conf, va_list *p);
int Choice(char *str, char symbol, spec conf, va_list *p);
int s21_Accuracy(int accuracy, int symbol);
int s21_ctos(char *str, va_list *p, char *flag, int accuracy, char type);
char *s21_conf(char *str, spec conf, char symbol);
char *s21_convert_string(char *str, va_list *p, int accuracy, char type);
char *s21_pointer_to_hex_string(char *str, int *variable);
char *s21_int_to_string(char *str, int number, int accuracy, char *flag);
char *s21_int_to_string_long(char *str, long int number, int accuracy,
                             char *flag);
char *s21_int_to_string_short(char *str, short int number, int accuracy,
                              char *flag);
char *s21_double_to_string_long(char *str, long double number, int accuracy,
                                char *flag, int symbol);
char *s21_double_to_string(char *str, double number, int accuracy, char *flag,
                           int symbol);
char *s21_float_to_string_long(char *str, long double number, int after,
                               char *flag, int fix_2);
char *s21_float_to_string(char *str, double number, int after, char *flag,
                          int fix_2);
char *s21_int_to_string_unsigned(char *str, unsigned int number, int format,
                                 int accuracy, char *flag);
char *s21_int_to_string_unsigned_long(char *str, unsigned long int number,
                                      int format, int accuracy, char *flag);
char *s21_int_to_string_unsigned_short(char *str, unsigned short int number,
                                       int format, int accuracy, char *flag);
char *s21_float_exp_string_long(char *str, long double number, int accuracy,
                                char *flag, int symbol, int fix_2);
char *s21_float_exp_string(char *str, double number, int accuracy, char *flag,
                           int symbol, int fix_2);
char *s21_strcat(char *dest, const char *src);
int s21_strcmp(const char *str1, const char *str2);
void *s21_memmove(void *dest, const void *src, size_t n);
#endif  // SRC_HEADERS_S21_SPRINTF_H_
