#ifndef _TEST_STRING_H_
#define _TEST_STRING_H_
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

Suite* test_s21_strlen();
Suite* test_s21_memcmp();
Suite* test_s21_memset();
Suite* test_s21_strncpy();
Suite* test_s21_strcspn();
Suite* test_s21_memcpy();
Suite* test_s21_strncmp();
Suite* test_s21_strncat();
Suite* test_s21_strerror();
Suite* test_s21_strtok();
Suite* test_s21_memchr();
Suite* test_s21_strchr();
Suite* test_s21_strpbrk();
Suite* test_s21_strrchr();
Suite* test_s21_strstr();

Suite* test_s21_sscanf_c();
Suite* test_s21_sscanf_d();
Suite* test_s21_sscanf_f();
Suite* test_s21_sscanf_s();
Suite* test_s21_sscanf_u();
Suite* test_s21_sscanf_e();
Suite* test_s21_sscanf_g();
Suite* test_s21_sscanf_x();
Suite* test_s21_sscanf_o();
Suite* test_s21_sscanf_p();
Suite* test_s21_sscanf_i();
Suite* test_s21_sscanf_n();

Suite* test_s21_sprintf_c();
Suite* test_s21_sprintf_d();
Suite* test_s21_sprintf_f();
Suite* test_s21_sprintf_s();
Suite* test_s21_sprintf_u();
Suite* test_s21_sprintf_e();
Suite* test_s21_sprintf_g();
Suite* test_s21_sprintf_x();
Suite* test_s21_sprintf_o();
Suite* test_s21_sprintf_p();
Suite* test_s21_sprintf_i();
Suite* test_s21_sprintf_n();

Suite* test_s21_to_upper();
Suite* test_s21_to_lower();
Suite* test_s21_insert();
Suite* test_s21_trim();

#endif  // _TEST_STRING_H_
