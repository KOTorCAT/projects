#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>

#define SIZE_DIGIT 90
#define BASE8 8
#define BASE16 16

typedef struct {
  int start;
  int startPattern;
  int endPattern;
  int digitDone;
  int lenPattern;
  char digit[SIZE_DIGIT];
  int number;
  char specificator;
  int h;
  int l;
  int L;
  int star;

  int countSymbols;

} formatPattern;

int s21_sscanf(const char *str, const char *format, ...);
int scaleNotation(char *number);
int isSpecificator(char format);
int isDigit(char format);
int isDigit16(char format);
int isFlags(char format);

int parseFormat(const char **str, const char **format,
                formatPattern *formatPattern, va_list *args, int *counter,
                const char *ptr7);
int validPattern(formatPattern formatPattern);
int readPattern(formatPattern formatPattern, const char **str, va_list *args,
                int *counter, const char *ptr);
void resetFormatPattern(formatPattern *formatPattern);
int readChar(const char **str, va_list *args, formatPattern *formatPattern);

int readD(const char **str, va_list *args, formatPattern *formatPattern);
int readI(const char **str, va_list *args, formatPattern *formatPattern);
int readFloat(const char **str, va_list *args, formatPattern *formatPattern);
int validFloat(char ch);
int readString(const char **str, va_list *args, formatPattern *formatPattern);
int readO(const char **str, va_list *args, formatPattern *formatPattern);
int readU(const char **str, va_list *args, formatPattern *formatPattern);
int readX(const char **str, va_list *args, formatPattern *formatPattern);
int readP(const char **str, va_list *args, formatPattern *formatPattern);
int readN(va_list *args, int count);
int isSpace(char ch);
int lenStr(const char *str);
int lenDigitOctal(const char *str);

long int toOctal(const char **str, int *countSymbols,
                 formatPattern *formatPattern);
int notHexadecimal(char ch);
long int toHexadecimal(const char **str, int base, int *countSymbols,
                       formatPattern *formatPattern);

int strToDigit(char *str);
int specificDigit(int digit, char *str);
int signMinus(char sign);
int stopCycl(int a, int b);

#endif
