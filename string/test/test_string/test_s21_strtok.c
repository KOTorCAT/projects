#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  char delim[] = " ";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_2) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  char delim[] = " !";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_3) {
  char str1[] = "Hello world!  d       dfds\n fsd    f  \t";
  char str2[] = "Hello world!  d       dfds\n fsd    f  \t";
  char delim[] = " !";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_4) {
  char str1[] = "Hello world!  d       dfds\n fsd    f  \t";
  char str2[] = "Hello world!  d       dfds\n fsd    f  \t";
  char delim[] = "\n\t !e";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_5) {
  char str1[] = "Hello wo\0rld!  d       dfds\n fsd    f  \t";
  char str2[] = "Hello wo\0rld!  d       dfds\n fsd    f  \t";
  char delim[] = "\n\t !e\0";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_6) {
  char str1[] = " ";
  char str2[] = " ";
  char delim[] = " ";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_7) {
  char str1[] = " ";
  char str2[] = " ";
  char delim[] = "";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_8) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = "";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_9) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = " ";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_10) {
  char str1[] =
      "djfhsdkj  sda   dlo23901o k\n \e\f wee\r  \er\\sdejldn je \\\ad qe2eq2";
  char str2[] =
      "djfhsdkj  sda   dlo23901o k\n \e\f wee\r  \er\\sdejldn je \\\ad qe2eq2";
  ;
  char delim[] = "klj ebfkqenb\n\e\f\r\e\\a2";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_11) {
  char str1[] = "Hello world!  d    Hello   dfHellods\n fsd   Hello f  \t";
  char str2[] = "Hello world!  d    Hello   dfHellods\n fsd   Hello f  \t";
  char delim[] = "Hello";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_12) {
  char str1[] = "Hello world!  d    Hello   dfHellods\n fsd   Hello f  \t";
  char str2[] = "Hello world!  d    Hello   dfHellods\n fsd   Hello f  \t";
  char delim[] = "Hello world!  d    Hello   dfHellods\n fsd   Hello f  \t";

  char* ptr1 = s21_strtok(str1, delim);
  char* ptr2 = strtok(str2, delim);

  while (ptr2 != NULL) {
    ck_assert_pstr_eq(ptr1, ptr2);

    ptr1 = s21_strtok(S21_NULL, delim);
    ptr2 = strtok(NULL, delim);
  }
}
END_TEST

Suite* test_s21_strtok() {
  Suite* s = suite_create("\033[33m S21_STRTOK \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strtok \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);

  suite_add_tcase(s, tc);
  return s;
}