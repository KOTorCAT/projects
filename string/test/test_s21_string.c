#include "test_s21_string.h"

// вернуть тест 14 у sprintf_s когда нибудь

#define ALL
//  #define SHARP
//  #define SSCANF_TEST
//  #define SPRINTF_TEST
int main() {
  setlocale(LC_ALL, "");

#ifdef SHARP
  Suite* tests[] = {test_s21_to_upper(), test_s21_to_lower(), test_s21_insert(),
                    test_s21_trim(), NULL};
#endif
#ifdef SSCANF_TEST
  Suite* tests[] = {test_s21_sscanf_c(),
                    test_s21_sscanf_d(),
                    test_s21_sscanf_f(),
                    test_s21_sscanf_s(),
                    test_s21_sscanf_u(),
                    test_s21_sscanf_e(),
                    test_s21_sscanf_g(),
                    test_s21_sscanf_x(),
                    test_s21_sscanf_o(),
                    test_s21_sscanf_p(),
                    test_s21_sscanf_i(),
                    test_s21_sscanf_n(),
                    NULL};
#endif
#ifdef SPRINTF_TEST
  Suite* tests[] = {test_s21_sprintf_c(),
                    test_s21_sprintf_d(),
                    test_s21_sprintf_f(),
                    test_s21_sprintf_s(),
                    test_s21_sprintf_u(),
                    test_s21_sprintf_e(),
                    test_s21_sprintf_g(),
                    test_s21_sprintf_x(),
                    test_s21_sprintf_o(),
                    test_s21_sprintf_p(),
                    test_s21_sprintf_i(),
                    test_s21_sprintf_n(),
                    NULL};
#endif
#ifdef ALL
  Suite* tests[] = {test_s21_strlen(),    test_s21_memcmp(),
                    test_s21_memset(),    test_s21_strncpy(),
                    test_s21_strcspn(),   test_s21_memcpy(),
                    test_s21_strncmp(),   test_s21_strncat(),
                    test_s21_memchr(),    test_s21_strchr(),
                    test_s21_strpbrk(),   test_s21_strrchr(),
                    test_s21_strstr(),    test_s21_strerror(),
                    test_s21_strtok(),    test_s21_sscanf_c(),
                    test_s21_sscanf_d(),  test_s21_sscanf_f(),
                    test_s21_sscanf_s(),  test_s21_sscanf_u(),
                    test_s21_sscanf_e(),  test_s21_sscanf_g(),
                    test_s21_sscanf_x(),  test_s21_sscanf_o(),
                    test_s21_sscanf_p(),  test_s21_sscanf_i(),
                    test_s21_sscanf_n(),  test_s21_sprintf_c(),
                    test_s21_sprintf_d(), test_s21_sprintf_f(),
                    test_s21_sprintf_s(), test_s21_sprintf_u(),
                    test_s21_sprintf_e(), test_s21_sprintf_g(),
                    test_s21_sprintf_x(), test_s21_sprintf_o(),
                    test_s21_sprintf_p(), test_s21_sprintf_i(),
                    test_s21_sprintf_n(), test_s21_to_upper(),
                    test_s21_to_lower(),  test_s21_insert(),
                    test_s21_trim(),      NULL};
#endif

  for (int i = 0; tests[i] != NULL; i++) {
    SRunner* sr = srunner_create(tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
  }
  return 0;
}
