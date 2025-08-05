#include "s21_sscanf.h"

#include <math.h>

#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int counter = 0, error = 0;
  const char *ptr = str;
  const char *string = str;
  va_list args;
  va_start(args, format);
  formatPattern formatPattern = {0, 0, 0, 0, 0, "\0", -1, '0', 0, 0, 0, 0, 0};
  while (*format) {
    if (!error) {
      error =
          parseFormat(&string, &format, &formatPattern, &args, &counter, ptr);
      format++;
      if (error) {
        break;
      }
    }
  }
  if (*str == '\0') counter = -1;
  va_end(args);
  return counter;
}
int isSpecificator(char format) {
  int result = 0;
  const char specificators[20] = "cdieEfgGosuXxpn";
  const char *ptr = specificators;
  while (*ptr != '\0') {
    if (*ptr == format) result = 1;
    ptr++;
  }

  return result;
}
int isDigit(char format) {
  int result = 0;
  const char specificators[20] = "0123456789";
  if (s21_strchr(specificators, format)) result = 1;
  return result;
}
int isDigit16(char format) {
  int result = 0;
  const char specificators[23] = "0123456789abcdefABCDEF";
  if (s21_strchr(specificators, format)) result = 1;
  return result;
}
int isFlags(char format) {
  int result = 0;
  const char specificators[20] = "hlL";
  if (s21_strchr(specificators, format)) result = 1;
  return result;
}
int parseFormat(const char **str, const char **format,
                formatPattern *formatPattern, va_list *args, int *counter,
                const char *ptr) {
  int error = 0;

  if (!error) {
    // if (**format == ' ' && !formatPattern->startPattern) (*format)++;
    formatPattern->lenPattern++;
    if (**format == ' ' && formatPattern->startPattern) error = 1;
    if (**format == '%') {
      formatPattern->startPattern++;
      if (formatPattern->startPattern > 1) {
        resetFormatPattern(formatPattern);
        if (*(*format + 1) != '%') error = 1;
        if (*(*format - 1) != '%') error = 1;
      }
    }
    if (**format == '*') {
      formatPattern->star++;
    }
    if (isDigit(**format) && formatPattern->startPattern &&
        formatPattern->digitDone == 0)
      s21_strncat(formatPattern->digit, *format, 1);
    if (!isDigit(**format) && s21_strlen(formatPattern->digit) > 0) {
      formatPattern->digitDone = 1;
    }
    if (**format == 'h' && formatPattern->startPattern == 1)
      formatPattern->h = 1;

    if (**format == 'L' && formatPattern->startPattern == 1)
      formatPattern->L = 1;

    if (**format == 'l' && formatPattern->startPattern == 1)
      formatPattern->l = 1;
    if (isDigit(**format) && formatPattern->digitDone == 1) error = 1;

    if (isSpecificator(**format) && formatPattern->startPattern > 0 && !error) {
      formatPattern->specificator = **format;
      error = readPattern(*formatPattern, str, args, counter, ptr);
      resetFormatPattern(formatPattern);
    }
  }
  return error;
}
int validPattern(formatPattern formatPattern) {
  int result = 0;
  if (formatPattern.startPattern == 1) result = 1;

  return result;
};
int readPattern(formatPattern formatPattern, const char **str, va_list *args,
                int *counter, const char *ptr) {
  int error = 0, flag = 0, countN = 0;
  switch (formatPattern.specificator) {
    case 'c': {
      if (**str != '\0') {
        *counter += readChar(str, args, &formatPattern);
        break;
      } else {
        error = 1;
        break;
      }
    }
    case 'd':
      flag = readD(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'i':
      flag = readI(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'e':
    case 'E':
    case 'F':
    case 'f':
    case 'g':
    case 'G':
      flag = readFloat(str, args, &formatPattern);
      if (flag == -1) {
        error = 1;
      }
      if (flag > 0) {
        (*counter)++;
      }
      break;
    case 's':
      *counter += readString(str, args, &formatPattern);
      break;
    case 'u':
      flag = readU(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'o':
      flag = readO(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'x':
    case 'X':
      flag = readX(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'p':
      flag = readP(str, args, &formatPattern);
      if (flag == -1) error = 1;
      if (flag > 0) (*counter)++;
      break;
    case 'n':
      countN = *str - ptr;
      *counter += readN(args, countN);
      break;
    default:
      break;
  }
  return error;
}
void resetFormatPattern(formatPattern *formatPattern) {
  formatPattern->start = 0;
  formatPattern->startPattern = 0;
  formatPattern->endPattern = 0;
  formatPattern->digitDone = 0;
  formatPattern->lenPattern = 0;
  s21_memcpy(formatPattern->digit, "\0", 1);
  formatPattern->number = -1;
  formatPattern->specificator = '0';
  formatPattern->h = 0;
  formatPattern->l = 0;
  formatPattern->L = 0;
  formatPattern->star = 0;
  formatPattern->countSymbols = 0;
}
int readD(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0, error = 0;
  short flag_minus = 1;
  long int number = 0;
  int countSymbols = 0;

  if (s21_strlen(formatPattern->digit) > 0) {
    formatPattern->number = strToDigit(formatPattern->digit);
  }
  while (isSpace(**str) || **str == '\t') {
    (*str)++;
    formatPattern->countSymbols++;
  }
  if (**str == '\0') error = -1;
  if (!isDigit(**str) && **str != '-' && **str != '+') {
    error = -1;
  }
  if (error == 0) {
    if (**str == '-' || **str == '+') {
      flag_minus = signMinus(**str);
      (*str)++;
      countSymbols++;
      formatPattern->countSymbols++;
    }
    if (!isDigit(**str)) error = -1;
    while ((**str >= '0' && **str <= '9') &&
           (countSymbols != formatPattern->number)) {
      number = number * 10 + **str - '0';
      (*str)++;
      countSymbols++;
      formatPattern->countSymbols++;
    }
    if (!formatPattern->star) {
      long int *numberLong = S21_NULL;
      int *numberInt = S21_NULL;
      short *numberShort = S21_NULL;

      if (formatPattern->h == 1) {
        numberShort = va_arg(*args, short int *);
        *numberShort = number * flag_minus;
        result = 1;
      }
      if (formatPattern->l) {
        numberLong = va_arg(*args, long int *);
        *numberLong = number * flag_minus;
        result = 1;
      }
      if (!formatPattern->l && !formatPattern->h) {
        numberInt = va_arg(*args, int *);
        *numberInt = number * flag_minus;
        result = 1;
      }
    }
  }
  if (error) result = -1;
  return result;
}
int specificDigit(int digit, char *str) {
  int result = digit;
  int countNumbers = 0;
  while (digit > 1) {
    digit = digit / 10;
    countNumbers++;
  }
  if (countNumbers >= (int)s21_strlen(str)) {
    result = 2;
  }

  return result;
}
int strToDigit(char *str) {
  int result = 0;

  while (*str != '\0') {
    result = result * 10 + *str - '0';
    str++;
  }
  return result;
}
int readChar(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0;
  char *n = S21_NULL;
  if (!formatPattern->star) {
    n = va_arg(*args, char *);
    *n = **str;
    result = 1;
  }
  (*str)++;

  return result;
}
int readFloat(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0, countSymbols = 0;
  long double number = 0.0, fractional = 0.1;
  int flag_fminus = 1, flag_minusEx = 1;
  if (s21_strlen(formatPattern->digit) > 0) {
    formatPattern->number = strToDigit(formatPattern->digit);
  }
  while (isSpace(**str)) (*str)++;

  if (validFloat(**str)) {
    if (**str == '-' || **str == '+') {
      flag_fminus = signMinus(**str);
      (*str)++;
      countSymbols++;
    }
    if (**str == '.') {
      (*str)++;
      countSymbols++;
      while ((**str >= '0' && **str <= '9') &&
             (countSymbols != formatPattern->number)) {
        number += (**str - '0') * fractional;
        fractional *= 0.1;
        (*str)++;
        countSymbols++;
      }
    }
    if (isDigit(**str)) {
      while ((**str >= '0' && **str <= '9') &&
             (countSymbols != formatPattern->number)) {
        number = number * 10 + (**str - '0');
        (*str)++;
        countSymbols++;
      }
      if (**str == '.' && countSymbols != formatPattern->number) {
        (*str)++;
        countSymbols++;
      }

      while ((**str >= '0' && **str <= '9') &&
             (countSymbols != formatPattern->number)) {
        number += (**str - '0') * fractional;
        fractional *= 0.1;
        (*str)++;
        countSymbols++;
      }
      long double mantissa = 0.0;
      if (**str == 'e' || **str == 'E') {
        (*str)++;
        countSymbols++;
        if (**str == '-' || **str == '+') {
          flag_minusEx = signMinus(**str);
          (*str)++;
          countSymbols++;
        }
        while ((**str >= '0' && **str <= '9') &&
               (countSymbols != formatPattern->number)) {
          mantissa = mantissa * 10 + (**str - '0');
          (*str)++;
          countSymbols++;
        }
        for (int i = 0; i < mantissa; i++) {
          if (flag_minusEx > 0) number *= 10;
          if (flag_minusEx < 0) {
            number = number / 10;
          }
        }
      }
    }
    float *numberFloat = S21_NULL;
    double *numberDouble = S21_NULL;
    long double *numberLong = S21_NULL;

    if (!formatPattern->star) {
      if (!formatPattern->L && !formatPattern->l) {
        numberFloat = va_arg(*args, float *);
        *numberFloat = number * flag_fminus;
        result = 1;
      }
      if (formatPattern->L) {
        numberLong = va_arg(*args, long double *);
        *numberLong = number * flag_fminus;
        result = 1;
      }
      if (formatPattern->l) {
        numberDouble = va_arg(*args, double *);
        *numberDouble = number * flag_fminus;
        result = 1;
      }
    }
  }

  else {
    result = -1;
  }
  return result;
}
int signMinus(char sign) {
  int result = 0;
  if (sign == '-') result = -1;
  if (sign == '+') result = 1;
  return result;
}
int validFloat(char ch) {
  int result = 0;
  const char symbols[20] = ".-+0123456789";
  const char *ptr = symbols;
  while (*ptr != '\0') {
    if (*ptr == ch) result = 1;
    ptr++;
  }
  return result;
}
int isSpace(char ch) {
  int result = 0;
  if (ch == ' ') result = 1;
  return result;
}
int lenStr(const char *str) {
  char *ptr = (char *)str;
  while (*ptr != ' ' && *ptr != '\0') ptr++;
  return ptr - str;
}
int lenDigitOctal(const char *str) {
  char *ptr = (char *)str;
  while (isDigit(*ptr) && *ptr < '8' && *ptr != '\0' && *ptr != ' ') {
    ptr++;
  }
  return ptr - str;
}
int lenDigitHexa(const char *str) {
  char *ptr = (char *)str;
  while (s21_strchr("1234567890ABCDEFabcdef", *ptr) && *ptr != '\0') {
    ptr++;
  }
  return ptr - str;
}
int readI(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0, countSymbols = 0, error = 0;
  short flag_minus = 1;
  int number = 0;

  while (isSpace(**str)) (*str)++;
  if (**str == '\0') error = -1;
  if (error == 0) {
    if (s21_strlen(formatPattern->digit) > 0) {
      formatPattern->number = strToDigit(formatPattern->digit);
    }

    if (**str == '-' || **str == '+') {
      flag_minus = signMinus(**str);
      (*str)++;
      countSymbols++;
    }
    if (!isDigit(**str)) error = 1;
    if (!error) {
      if (**str == '0') {
        if (*(*str + 1) == 'x' || *(*str + 1) == 'X') {
          (*str)++;
          (*str)++;
          countSymbols += 2;
          number = toHexadecimal(str, BASE16, &countSymbols, formatPattern);
        } else {
          number = toOctal(str, &countSymbols, formatPattern);
        }
      } else {
        while ((**str >= '0' && **str <= '9') &&
               countSymbols != formatPattern->number) {
          number = number * 10 + **str - '0';
          (*str)++;
          countSymbols++;
          if (!isDigit(**str) && **str != ' ') {
            break;
          }
        }
      }

      if (!formatPattern->star) {
        long int *numberLong = S21_NULL;
        int *numberInt = S21_NULL;
        short *numberShort = S21_NULL;

        if (formatPattern->h == 1) {
          numberShort = va_arg(*args, short int *);
          *numberShort = number * flag_minus;
          result = 1;
        }
        if (formatPattern->l) {
          numberLong = va_arg(*args, long int *);
          *numberLong = number * flag_minus;
          result = 1;
        }
        if (!formatPattern->l && !formatPattern->h) {
          numberInt = va_arg(*args, int *);
          *numberInt = number * flag_minus;
          result = 1;
        }
      }
    }
  }
  if (error) result = -1;
  return result;
}
long int toOctal(const char **str, int *countSymbols,
                 formatPattern *formatPattern) {
  int result = 0;
  int len = lenDigitOctal(*str);
  int n = len - 1;
  int i = 0;
  result = 0;
  while (i != len && *countSymbols != formatPattern->number) {
    if (**str >= '0' && **str <= '7') {
      result = result * 8 + (**str - '0');
      n--;
    } else {
      break;
    }
    (*str)++;
    (*countSymbols)++;
    i++;
  }
  return result;
}
int notHexadecimal(char ch) {
  int result = 0;
  const char symbols[23] = "0123456789abcdefABCDEF";
  if (s21_strchr(symbols, ch)) result = 1;
  return result;
}
long int toHexadecimal(const char **str, int base, int *countSymbols,
                       formatPattern *formatPattern) {
  long int result = 0;
  int len = lenDigitHexa(*str);
  int i = 0;
  while (i != len && *countSymbols != formatPattern->number) {
    if (**str >= '0' && **str <= '9') result = result * base + (**str - '0');
    if (**str >= 'a' && **str <= 'f')
      result = result * base + (10 + **str - 'a');
    if (**str >= 'A' && **str <= 'F')
      result = result * base + (10 + **str - 'A');
    i++;
    (*str)++;
    (*countSymbols)++;
  }
  return result;
}
int stopCycl(int a, int b) {
  int result = 0;
  if (a == b) result = 1;
  return result;
}
int readString(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0, error = 0, size = 3, count = 0;
  int countSymbols = 0;
  char *buff = S21_NULL;

  buff = (char *)malloc(size);
  if (!buff) {
    error = 1;
  }

  if (s21_strlen(formatPattern->digit) > 0) {
    formatPattern->number = strToDigit(formatPattern->digit);
  }
  while ((isSpace(**str) || **str == '\t') && !error) {
    (*str)++;
  }

  while (**str != ' ' && **str != '\0' && **str != '\t' && !error &&
         countSymbols != formatPattern->number) {
    if (count >= size - 1) {
      char *newBuff = realloc(buff, size *= 2);
      if (!newBuff) {
        error = 1;
        break;
      }
      buff = newBuff;
    }

    buff[count++] = **str;
    (*str)++;
    countSymbols++;
  }
  buff[count] = '\0';
  if (!formatPattern->star) {
    char *n = va_arg(*args, char *);
    s21_strncpy(n, buff, count);
    result = 1;
  }
  while (isSpace(**str) || **str == '\t') {
    (*str)++;
  }
  if (buff) free(buff);

  return result;
}
int readO(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0, countSymbols = 0, error = 0;
  long int number = 0;
  int flag_minus = 1;
  while (isSpace(**str)) (*str)++;
  if (s21_strlen(formatPattern->digit) > 0)
    formatPattern->number = strToDigit(formatPattern->digit);

  if (**str == '-' || **str == '+') {
    flag_minus = signMinus(**str);
    (*str)++;
    countSymbols++;
  }
  if (!(**str >= '0' && **str <= '7')) error = 1;

  if (!error) {
    number = toOctal(str, &countSymbols, formatPattern);
    if (!formatPattern->star) {
      long int *numberLong = S21_NULL;
      int *numberInt = S21_NULL;
      short *numberShort = S21_NULL;

      if (formatPattern->h == 1) {
        numberShort = va_arg(*args, short int *);
        *numberShort = number * flag_minus;
        result = 1;
      }
      if (formatPattern->l) {
        numberLong = va_arg(*args, long int *);
        *numberLong = number * flag_minus;
        result = 1;
      }
      if (!formatPattern->l && !formatPattern->h) {
        numberInt = va_arg(*args, int *);
        *numberInt = number * flag_minus;
        result = 1;
      }
    }
  }
  if (error) result = -1;
  return result;
}
int readU(const char **str, va_list *args, formatPattern *formatPattern) {
  unsigned int result = 0;
  int number = 0;
  int error = 0;
  int flag_minus = 1;
  int countSymbols = 0;
  while (isSpace(**str)) (*str)++;
  if (**str == '\0') error = -1;
  if (!isDigit(**str) && **str != '-' && **str != '+') error = -1;
  if (!error) {
    if (s21_strlen(formatPattern->digit) > 0) {
      formatPattern->number = strToDigit(formatPattern->digit);
    }

    if (**str == '-' || **str == '+') {
      flag_minus = signMinus(**str);
      (*str)++;
      countSymbols++;
    }
    while (**str >= '0' && **str <= '9' &&
           (countSymbols != formatPattern->number)) {
      number = number * 10 + **str - '0';
      (*str)++;
      countSymbols++;
    }
    if (!formatPattern->star) {
      unsigned long int *numberLong = S21_NULL;
      unsigned int *numberInt = S21_NULL;
      unsigned short *numberShort = S21_NULL;

      if (formatPattern->h == 1) {
        numberShort = va_arg(*args, unsigned short int *);
        *numberShort = number * flag_minus;
        result = 1;
      }
      if (formatPattern->l) {
        numberLong = va_arg(*args, unsigned long int *);
        *numberLong = number * flag_minus;
        result = 1;
      }
      if (!formatPattern->l && !formatPattern->h) {
        numberInt = va_arg(*args, unsigned int *);
        *numberInt = number * flag_minus;
        result = 1;
      }
    }
  }

  return result;
}
int readX(const char **str, va_list *args, formatPattern *formatPattern) {
  unsigned int result = 0;
  long int number = 0;
  int error = 0, countSymbols = 0;
  int flag_minus = 1;
  if (**str == '\0') error = -1;
  while (isSpace(**str) || **str == '\t') (*str)++;
  if (s21_strlen(formatPattern->digit) > 0) {
    formatPattern->number = strToDigit(formatPattern->digit);
  }
  if (**str == '-' || **str == '+') {
    flag_minus = signMinus(**str);
    (*str)++;
  }
  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    (*str)++;
    (*str)++;
  }
  if (!isDigit16(**str)) error = -1;
  if (error == 0) {
    number = toHexadecimal(str, BASE16, &countSymbols, formatPattern);

    if (!formatPattern->star) {
      long int *numberLong = S21_NULL;
      int *numberInt = S21_NULL;
      short *numberShort = S21_NULL;

      if (formatPattern->h == 1) {
        numberShort = va_arg(*args, short int *);
        *numberShort = number * flag_minus;
        result = 1;
      }
      if (formatPattern->l) {
        numberLong = va_arg(*args, long int *);
        *numberLong = number * flag_minus;
        result = 1;
      }
      if (!formatPattern->l && !formatPattern->h) {
        numberInt = va_arg(*args, int *);
        *numberInt = number * flag_minus;
        result = 1;
      }
    }
  }
  return result;
}

int readP(const char **str, va_list *args, formatPattern *formatPattern) {
  int result = 0;
  int error = 0;
  int countSymbols = 0;
  long int number = 0;
  while (isSpace(**str)) (*str)++;
  if (**str == '\0') error = -1;
  if (error == 0) {
    if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
      (*str)++;
      (*str)++;
      countSymbols += 2;
    }
    if (s21_strlen(formatPattern->digit) > 0)
      formatPattern->number = strToDigit(formatPattern->digit);
    if (error == 0) {
      number = toHexadecimal(str, BASE16, &countSymbols, formatPattern);
    }
    if (!formatPattern->star) {
      long int *numberInt = va_arg(*args, long int *);
      *numberInt = number;
      result = 1;
    }
  }
  return result;
}

int readN(va_list *args, int count) {
  int result = 0;
  int *n = va_arg(*args, int *);
  if (n) {
    *n = count;
  }

  return result;
}
