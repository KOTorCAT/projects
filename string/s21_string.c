#include "s21_string.h"
// 1
void* s21_memchr(const void* s, int c, s21_size_t n) {
  const unsigned char* p = s;
  void* result = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c) {
      result = (void*)(p + i);
      break;
    }
  }
  return result;
}
// 2
int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* p1 = (const unsigned char*)str1;
  const unsigned char* p2 = (const unsigned char*)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (*(p1 + i) != *(p2 + i)) {
      return *(p1 + i) - *(p2 + i);
    }
  }
  return 0;
}
// 3

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i += 1) {
    ((char*)dest)[i] = ((char*)src)[i];
  }
  return dest;
}

// 4

void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char* p = (unsigned char*)str;
  for (s21_size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return str;
}
// 5

char* s21_strncat(char* dest, const char* src, size_t n) {
  s21_size_t lenDest = s21_strlen(dest);

  for (s21_size_t i = 0; i < n; i++) {
    dest[lenDest + i] = src[i];
    dest[lenDest + i + 1] = '\0';
  }
  return dest;
}

// 6
char* s21_strchr(const char* s, int c) {
  char* result = S21_NULL;
  while (*s) {
    if (*s == (char)c) {
      result = (char*)s;
      break;
    }
    s++;
  }
  if (!result && c == '\0') {
    result = (char*)s;
  }
  return result;
}

// 7

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) result = str1[i] - str2[i];
    if (str1[i] == '\0' || str2[i] == '\0') {
      break;
    }
  }
  return result;
}

// 8

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}

// 9

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t str1_len = s21_strlen(str1);
  s21_size_t str2_len = s21_strlen(str2);
  s21_size_t len = 0;

  for (s21_size_t i = 0; i < str1_len; i++) {
    for (s21_size_t j = 0; j < str2_len; j++) {
      if (str1[i] == str2[j]) {
        return len;
      }
    }
    len++;
  }

  return len;
}

// 10

char* s21_strerror(int errnum) {
  static char result[500] = {};
  if (errnum > MIN_ERR && errnum < MAX_ERR)
    s21_memcpy(result, listError[errnum], s21_strlen(listError[errnum]));
  else {
    s21_sprintf(result, "Unknown error %d", errnum);
  }
  return result;
}

// 11

s21_size_t s21_strlen(const char* str) {
  s21_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

// 12

char* s21_strpbrk(const char* s1, const char* s2) {
  char* result = S21_NULL;
  while (*s1 && !result) {
    for (const char* p = s2; *p && !result; p++) {
      if (*s1 == *p) {
        result = (char*)s1;
      }
    }
    s1++;
  }
  return result;
}

// 13

char* s21_strrchr(const char* s, int c) {
  char* result = S21_NULL;
  while (*s) {
    if (*s == (char)c) {
      result = s;
    }
    s++;
  }
  if (!result && c == '\0') {
    result = (char*)s;
  }
  return result;
}

// 14

char* s21_strstr(const char* s, const char* n) {
  if (!*n) {
    return s;
  }
  char* result = S21_NULL;
  s21_size_t size = s21_strlen(n);
  while (*s) {
    if (*s == *n) {
      if (!s21_strncmp(s, n, size)) {
        return s;
      }
    }
    s++;
  }
  return result;
}

// 15

char* s21_strtok(char* str, const char* delim) {
  static char* last_str = S21_NULL;
  if (str) last_str = str;
  if (!last_str) return S21_NULL;

  while (*last_str && s21_strchr(delim, *last_str)) ++last_str;
  str = last_str;
  while (*last_str && !s21_strchr(delim, *last_str)) ++last_str;

  if (*last_str) {
    *last_str = '\0';
    last_str++;
  } else if (last_str == str) {
    return S21_NULL;
  }
  return str;
}

// 16

void* s21_to_upper(const char* str) {
  char* res = S21_NULL;
  if (str != S21_NULL) {
    int len = s21_strlen(str);
    res = malloc(sizeof(char) * len + 1);
    if (res != S21_NULL) {
      for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          res[i] = str[i] - 32;
        } else {
          res[i] = str[i];
        }
      }
      res[len] = '\0';
    }
  }
  return res;
}

// 17

void* s21_to_lower(const char* str) {
  char* res = S21_NULL;
  if (str != S21_NULL) {
    int len = s21_strlen(str);
    res = malloc(sizeof(char) * len + 1);
    if (res != S21_NULL) {
      for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          res[i] = str[i] + 32;
        } else {
          res[i] = str[i];
        }
      }
      res[len] = '\0';
    }
  }
  return res;
}

// 18

void* s21_insert(const char* src, const char* str, size_t start_index) {
  char* res = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    int len_src = s21_strlen(src);
    int len_str = s21_strlen(str);
    if (start_index >= 0 && start_index < len_src) {
      res = malloc(sizeof(char) * (len_src + len_str + 1));
      if (res != S21_NULL) {
        int index = 0;
        while (index < start_index) {
          res[index] = src[index];
          index++;
        }
        for (int i = 0; i < len_str; i++) {
          res[index] = str[i];
          index++;
        }
        for (int i = start_index; i < len_src; i++) {
          res[index] = src[i];
          index++;
        }
        res[len_src + len_str] = '\0';
      }
    }
  }
  return res;
}

// 20

void* s21_trim(const char* src, const char* trim_chars) {
  char* res = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    char* left = (char*)src;
    char* right = (char*)src + s21_strlen(src) - 1;
    while (*left && s21_strchr(trim_chars, *left)) {
      left++;
    }
    while (right > left && s21_strchr(trim_chars, *right)) {
      right--;
    }
    res = malloc((right - left + 2) * sizeof(char));
    if (res != S21_NULL) {
      s21_memcpy(res, left, right - left + 1);
      res[right - left + 1] = '\0';
    }
  }
  return res;
}
