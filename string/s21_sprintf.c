
#include "s21_sprintf.h"

#include "s21_string.h"
int s21_sprintf(char *str, const char *f, ...) {
  str[0] = '\0';
  va_list p;
  va_start(p, f);
  int c = 0;
  for (int x = 0; f[x] != '\0'; x += 1) {
    if (f[x] == '%') {
      spec conf = {"xxxxx", INT_MIN, INT_MIN, 'x'};
      x = specifier(x, f, &conf, &p);
      if (f[x] == 'n') {
        *(va_arg(p, int *)) = c;
      } else {
        c += Choice(str + c, f[x], conf, &p);
      }
    } else {
      str[c] = f[x];
      str[c += 1] = '\0';
    }
  }
  va_end(p);
  return c;
}
int s21_Accuracy(int accuracy, int symbol) {
  if (accuracy < 0) {
    s21_strchr("diouxX", symbol) ? accuracy = 1 : 0;
    s21_strchr("eEfgG", symbol) ? accuracy = 6 : 0;
    s21_strchr("p", symbol) ? accuracy = 16 : 0;
  }
  return accuracy;
}
int Choice(char *str, char symbol, spec conf, va_list *p) {
  char *flag = conf.flag;
  int indent = 0, accuracy = s21_Accuracy(conf.accuracy, symbol);
  if (symbol == '%') {
    s21_strcat(str, "%");
  } else if (symbol == 'c') {
    return s21_ctos(str + indent, p, flag, conf.width, conf.type);
  } else if (s21_strchr("di", symbol)) {
    if (conf.type == 'h')
      s21_int_to_string_short(str + indent, va_arg(*p, int), accuracy, flag);
    else if (conf.type == 'l')
      s21_int_to_string_long(str + indent, va_arg(*p, long int), accuracy,
                             flag);
    else
      s21_int_to_string(str + indent, va_arg(*p, int), accuracy, flag);
  } else if (symbol == 'p') {
    s21_pointer_to_hex_string(str + indent, va_arg(*p, void *));
  } else if (symbol == 's') {
    s21_convert_string(str + indent, p, accuracy, conf.type);
  } else if (symbol == 'f') {
    if (conf.type == 'L')
      s21_float_to_string_long(str + indent, va_arg(*p, long double), accuracy,
                               flag, 0);
    else
      s21_float_to_string(str + indent, va_arg(*p, double), accuracy, flag, 0);
  } else if (s21_strchr("gG", symbol)) {
    if (conf.type == 'L')
      s21_double_to_string_long(str + indent, va_arg(*p, long double), accuracy,
                                flag, symbol);
    else
      s21_double_to_string(str + indent, va_arg(*p, double), accuracy, flag,
                           symbol);
  } else if (s21_strchr("eE", symbol)) {
    if (conf.type == 'L')
      s21_float_exp_string_long(str + indent, va_arg(*p, long double), accuracy,
                                flag, symbol, 0);
    else
      s21_float_exp_string(str + indent, va_arg(*p, double), accuracy, flag,
                           symbol, 0);
  } else if (s21_strchr("xX", symbol)) {
    if (conf.type == 'h')
      s21_int_to_string_unsigned_short(str + indent, va_arg(*p, int),
                                       symbol == 'x' ? 32 : 16, accuracy, flag);
    else if (conf.type == 'l')
      s21_int_to_string_unsigned_long(str + indent, va_arg(*p, long int),
                                      symbol == 'x' ? 32 : 16, accuracy, flag);
    else
      s21_int_to_string_unsigned(str + indent, va_arg(*p, int),
                                 symbol == 'x' ? 32 : 16, accuracy, flag);
  } else if (symbol == 'o') {
    if (conf.type == 'h')
      s21_int_to_string_unsigned_short(str + indent, va_arg(*p, unsigned int),
                                       8, accuracy, flag);
    else if (conf.type == 'l')
      s21_int_to_string_unsigned_long(
          str + indent, va_arg(*p, long unsigned int), 8, accuracy, flag);
    else
      s21_int_to_string_unsigned(str + indent, va_arg(*p, unsigned int), 8,
                                 accuracy, flag);
  } else if (symbol == 'u') {
    if (conf.type == 'h')
      s21_int_to_string_unsigned_short(str + indent, va_arg(*p, unsigned int),
                                       10, accuracy, flag);
    else if (conf.type == 'l')
      s21_int_to_string_unsigned_long(
          str + indent, va_arg(*p, long unsigned int), 10, accuracy, flag);
    else
      s21_int_to_string_unsigned(str + indent, va_arg(*p, unsigned int), 10,
                                 accuracy, flag);
  }
  s21_strchr("n%c", symbol) ? 0 : s21_conf(str + indent, conf, symbol);
  return s21_strlen(str);
}
int specifier(int x, const char *format, spec *conf, va_list *p) {
  for (x += 1; s21_strchr("-+ #0", format[x]); x += 1)
    (conf->flag)[5 - s21_strlen(s21_strchr("-+ #0", format[x]))] = 'o';
  for (; s21_strchr("0123456789", format[x]); x += 1)
    conf->width = (conf->width * 10) + (format[x] - 48);
  for (; format[x] == '*'; x += 1) conf->width = va_arg(*p, int);
  if (format[x] == '.') {
    for (x += 1; format[x] == '-'; x += 1) continue;
    for (; s21_strchr("0123456789", format[x]); x += 1)
      conf->accuracy = (conf->accuracy * 10) + (format[x] - 48);
    for (; format[x] == '*'; x += 1) conf->accuracy = va_arg(*p, int);
    conf->accuracy < 0 ? conf->accuracy = 0 : 0;
  }
  for (; s21_strchr("hlL", format[x]); x += 1) conf->type = format[x];
  return x;
}
char *s21_double_to_string_long(char *str, long double number, int accuracy,
                                char *flag, int symbol) {
  int lenNum = 0;
  accuracy == 0 ? accuracy = 1 : 0;
  if (number == 0) {
    s21_float_to_string_long(str, number, accuracy - 1, flag, 1);
  } else {
    for (int dop = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         dop != 0; lenNum += dop)
      dop = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? dop
                : 0;
    if (lenNum <= 0)
      (accuracy + lenNum <= 0)
          ? s21_float_exp_string_long(str, number, accuracy - 1, flag,
                                      symbol - 2, 1)
          : s21_float_to_string_long(str, number, (accuracy - 1) + lenNum, flag,
                                     1);
    else
      (accuracy - 1) <= lenNum
          ? s21_float_exp_string_long(str, number, accuracy - 1, flag,
                                      symbol - 2, 1)
          : s21_float_to_string_long(str, number, lenNum + (accuracy - 1), flag,
                                     1);
  }
  return str;
}
char *s21_int_to_string(char *str, int number, int accuracy, char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}
char *s21_conf(char *str, spec conf, char symbol) {
  if (s21_strcmp(conf.flag, "xxxxx") || conf.width >= 0 || conf.type != 'x') {
    if (s21_strchr("gG", symbol) && conf.flag[3] != 'o') {
      if (!(s21_strlen(str) == 1 && str[0] == '0')) {
        for (int x = (s21_strlen(str) - 1); str[x] == '0';
             str[x] = '\0', x -= 1)
          continue;
      }
    }
  }
  char *dop = str;
  char filler = ' ';
  int countFill = conf.width > 0 ? conf.width - s21_strlen(str) : 0;
  if (conf.flag[4] == 'o') {
    dop[0] == '-' ? dop += 1 : 0;
    s21_strchr("cs", symbol) ? 0 : (filler = '0');
  } else if (conf.flag[0] == 'o') {
    dop += s21_strlen(dop);
  }
  if (countFill > 0) {
    for (s21_memmove(dop + countFill, dop, s21_strlen(dop) + 1);
         countFill != 0;) {
      dop[countFill - 1] = filler;
      countFill -= 1;
    }
  }
  return str;
}
int s21_ctos(char *str, va_list *p, char *flag, int accuracy, char type) {
  int c = 0;
  accuracy = accuracy < 1 ? 1 : accuracy;
  if (type == 'l') {
    wchar_t w_c = va_arg(*p, wchar_t);
    c = wcstombs(str + c, &w_c, 512);
  } else {
    str[c++] = va_arg(*p, int);
    str[c] = '\0';
  }
  if (flag[0] != 'o' && accuracy - c > 0) {
    s21_memmove(str + (accuracy - c), str, c + 1);
    for (int x = 0; x < accuracy - c; x += 1) str[x] = ' ';
    c = accuracy;
  }
  for (int x = c; flag[0] == 'o' && x < (accuracy); x += 1) str[c++] = ' ';
  return c;
}
char *s21_convert_string(char *str, va_list *p, int accuracy, char type) {
  if (type == 'l') {
    wcstombs(str, va_arg(*p, wchar_t *), 512);
  } else {
    s21_strcat(str, va_arg(*p, char *));
  }
  accuracy < 0 ? accuracy = s21_strlen(str) : 0;
  str[accuracy] = '\0';
  return str;
}
char *s21_pointer_to_hex_string(char *str, int *variable) {
  int *dop = variable;
  if (dop == NULL) {
    s21_strcat(str, "0x0");
  } else {
    for (int x = s21_strlen(str); dop != 0;
         dop = ((void *)(((size_t)dop) >> 4)), x += 1) {
      unsigned int last_symbol = ((size_t)dop) % 0x10;
      last_symbol < 10 ? (str[x] = ('0' + last_symbol))
                       : (str[x] = ('a' + (last_symbol - 10)));
      str[x + 1] = '\0';
    }
    s21_strcat(str, "x0");
    s21_reverse(str);
  }
  return str;
}
char *s21_int_to_string_unsigned(char *str, unsigned int number, int format,
                                 int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}
char *s21_float_to_string_long(char *str, long double number, int after,
                               char *flag, int fix_2) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, fix = after, k3 = 0;
  for (; number < 0; number *= (-1), minus = 1) continue;
  long double dop = ceill((number - truncl(number)) * powl(10, after) - 0.5);
  for (; ((after != 0) || ((dop / 10) > 1) || (fmodl(dop, 10) > 1));
       after -= 1, dop /= 10) {
    str[lenStr++] = ((int)fmodl(dop, 10)) + 48;
    str[lenStr] = '\0';
  }
  dop == 1 ? k3 = 1 : 0;
  (fix != 0 || flag[3] == 'o')
      ? str[lenStr++] = (localeconv()->decimal_point)[0]
      : 0;
  fix == 0 ? number = roundl(number) : 0;
  for (dop = k3 == 1 ? round(number) : number; ((dop / 10) >= 1);
       dop /= 10, str[lenStr] = '\0')
    str[lenStr++] = ((int)fmodl(dop, 10)) + 48;
  s21_int_to_string(str + lenStr, fmodl(dop, 10), 1, flagX);
  minus == 1 ? s21_strcat(str, "-") : 0;
  lenStr = s21_strlen(str);
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
    str[lenStr] = '\0';
  }
  s21_reverse(str);
  if (fix_2 == 1 && flag[3] != 'o') {
    int x = s21_strlen(str) - 1;
    for (; s21_strchr("0", str[x]); str[x--] = '\0') continue;
    str[x] == (localeconv()->decimal_point)[0] ? str[x] = '\0' : 0;
  }
  return str;
}
char *s21_int_to_string_unsigned_long(char *str, long unsigned int number,
                                      int format, int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}
char *s21_int_to_string_long(char *str, long int number, int accuracy,
                             char *flag) {
  int lenStr = 0;
  long int minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}
char *s21_int_to_string_unsigned_short(char *str, short unsigned int number,
                                       int format, int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}
char *s21_int_to_string_short(char *str, short int number, int accuracy,
                              char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}
char *s21_float_exp_string(char *str, double number, int accuracy, char *flag,
                           int symbol, int fix_2) {
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";
  int lenStr = 0, lenNum = 0, res = 0, fix = accuracy;
  if (number != 0) {
    for (int dop = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         dop != 0; lenNum += dop)
      dop = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? dop
                : 0;
  }
  s21_int_to_string(str,
                    (fix == 0 ? (round(number * pow(10, lenNum)))
                              : (number * pow(10, lenNum))),
                    1, flag);
  (fix != 0 || flag[3] == 'o') ? s21_strcat(str, (localeconv()->decimal_point))
                               : 0;
  for (lenStr = s21_strlen(str); number < 0; number *= (-1)) continue;
  for (res = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1) {
    if (accuracy == 1)
      s21_int_to_string(str + (lenStr++),
                        fmod((round(number) * pow(10, lenNum += 1)), 10), 1,
                        flagX);
    else
      s21_int_to_string(str + (lenStr++),
                        fmod((number * pow(10, lenNum += 1)), 10), 1, flagX);
  }
  for (int dop = lenNum + 1; accuracy != 0; accuracy -= 1)
    accuracy == 1
        ? s21_int_to_string(str + (lenStr++),
                            round(fmod((number * pow(10, (dop++))), 10)), 1,
                            flagX)
        : s21_int_to_string(str + (lenStr++),
                            fmod((number * pow(10, (dop++))), 10), 1, flagX);
  if (fix_2 == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(str) - 1; s21_strchr("0", str[x]); str[x--] = '\0')
      continue;
    for (int x = s21_strlen(str) - 1;
         s21_strchr((localeconv()->decimal_point), str[x]);)
      str[x--] = '\0';
  }
  lenStr = s21_strlen(str);
  str[lenStr++] = symbol;
  str[lenStr] = '\0';
  s21_int_to_string(str + (lenStr), -res, 2, flag1);
  return str;
}
char *s21_float_exp_string_long(char *str, long double number, int accuracy,
                                char *flag, int symbol, int fix_2) {
  int lenStr = 0, lenNum = 0, res = 0, fix = accuracy;
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";
  if (number != 0) {
    for (int dop = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         dop != 0; lenNum += dop)
      dop = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? dop
                : 0;
  }
  s21_int_to_string(str,
                    (fix == 0 ? (roundl(number * powl(10, lenNum)))
                              : (number * powl(10, lenNum))),
                    1, flag);
  (fix != 0 || flag[3] == 'o') ? s21_strcat(str, (localeconv()->decimal_point))
                               : 0;
  for (lenStr = s21_strlen(str); number < 0; number *= (-1)) continue;
  for (res = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1) {
    if (accuracy == 1)
      s21_int_to_string(
          str + (lenStr++),
          roundl(fmodl((roundl(number) * powl(10, lenNum += 1)), 10)), 1,
          flagX);
    else
      s21_int_to_string(str + (lenStr++),
                        fmodl((number * powl(10, lenNum += 1)), 10), 1, flagX);
  }
  for (int dop = lenNum + 1; accuracy != 0; accuracy -= 1) {
    if (accuracy == 1)
      s21_int_to_string(str + (lenStr++),
                        roundl(fmodl((number * powl(10, (dop++))), 10)), 1,
                        flagX);
    else
      s21_int_to_string(str + (lenStr++),
                        fmodl((number * powl(10, (dop++))), 10), 1, flagX);
  }
  if (fix_2 == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(str) - 1; s21_strchr("0.", str[x]); str[x--] = '\0')
      continue;
    for (int x = s21_strlen(str) - 1;
         s21_strchr((localeconv()->decimal_point), str[x]);)
      str[x--] = '\0';
  }
  lenStr = s21_strlen(str);
  str[lenStr++] = symbol;
  str[lenStr] = '\0';
  s21_int_to_string(str + (lenStr), -res, 2, flag1);
  return str;
}
char *s21_float_to_string(char *str, double number, int after, char *flag,
                          int fix_2) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, fix = after, k3 = 0;
  for (; number < 0; number *= (-1), minus = 1) continue;
  double dop = ceil((number - trunc(number)) * pow(10, after) - 0.5);
  for (; ((after != 0) || ((dop / 10) > 1) || (fmod(dop, 10) > 1));
       after -= 1, dop /= 10) {
    str[lenStr++] = ((int)fmod(dop, 10)) + 48;
    str[lenStr] = '\0';
  }
  dop == 1 ? k3 = 1 : 0;
  (fix != 0 || flag[3] == 'o')
      ? str[lenStr++] = (localeconv()->decimal_point)[0]
      : 0;
  fix == 0 ? number = round(number) : 0;
  for (dop = k3 == 1 ? round(number) : number; (dop / 10 >= 1);
       dop /= 10, str[lenStr] = '\0')
    str[lenStr++] = ((int)fmod(dop, 10)) + 48;
  s21_int_to_string(str + lenStr, fmod(dop, 10), 1, flagX);
  minus == 1 ? s21_strcat(str, "-") : 0;
  lenStr = s21_strlen(str);
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
    str[lenStr] = '\0';
  }
  s21_reverse(str);
  if (fix_2 == 1 && flag[3] != 'o') {
    int x = s21_strlen(str) - 1;
    for (; s21_strchr("0", str[x]); str[x--] = '\0') continue;
    str[x] == (localeconv()->decimal_point)[0] ? str[x] = '\0' : 0;
  }
  return str;
}
char *s21_strcat(char *destptr, const char *srcptr) {
  int destptrLength = s21_strlen(destptr);
  int srcptrLength = s21_strlen(srcptr);
  for (int x = 0; x <= srcptrLength; x += 1)
    destptr[destptrLength + x] = srcptr[x];
  return destptr;
}
char *s21_reverse(char *str) {
  int lenStr = s21_strlen(str);
  for (int x = 0; x < (lenStr / 2); x += 1) {
    char dop = str[lenStr - 1 - x];
    str[lenStr - 1 - x] = str[x];
    str[x] = dop;
  }
  return str;
}
int s21_strcmp(const char *str_1, const char *str_2) {
  int res = 0;
  for (int x = 0; res == 0 && str_1[x] != '\0' && str_2[x] != '\0'; x += 1)
    if (str_1[x] != str_2[x]) res = str_1[x] - str_2[x];
  return res == 0 ? 0 : (res > 0 ? 1 : (-1));
}
void *s21_memmove(void *dest, const void *src, s21_size_t size) {
  char *d = (char *)dest;
  const char *s = (const char *)src;

  if (d == s || size == 0) {
    return dest;
  }

  if (d < s) {
    for (s21_size_t i = 0; i < size; i++) {
      d[i] = s[i];
    }
  } else {
    for (s21_size_t i = size; i > 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }

  return dest;
}
char *s21_double_to_string(char *str, double number, int accuracy, char *flag,
                           int symbol) {
  int lenNum = 0;
  accuracy == 0 ? accuracy = 1 : 0;
  if (number == 0) {
    s21_float_to_string(str, number, accuracy - 1, flag, 1);
  } else {
    for (int dop = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         dop != 0; lenNum += dop)
      dop = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? dop
                : 0;
    if (lenNum <= 0)
      (accuracy + lenNum <= 0)
          ? s21_float_exp_string(str, number, accuracy - 1, flag, symbol - 2, 1)
          : s21_float_to_string(str, number, (accuracy - 1) + lenNum, flag, 1);
    else
      lenNum > 4
          ? s21_float_exp_string(str, number, accuracy - 1, flag, symbol - 2, 1)
          : s21_float_to_string(str, number, lenNum + (accuracy - 1), flag, 1);
  }
  return str;
}
