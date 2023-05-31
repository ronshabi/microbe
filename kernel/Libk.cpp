#include <kernel/Libk.h>

size_t strlen(const char* str) {
  size_t len = 0;
  while (*str++)
    len++;
  return len;
}

int memcmp(const void* s1, const void* s2, size_t n) {
  int diff = 0;

  for (size_t i = 0; i < n; i++)
    diff += ((const char*)s1)[i] - ((const char*)s2)[i];

  return diff;
}

void* memcpy(void* dest, const void* src, size_t n) {
  for (size_t i = 0; i < n; i++)
    ((char*)dest)[i] = ((char*)src)[i];

  return dest;
}

void* memmove(void* dstptr, const void* srcptr, size_t size) {
  unsigned char* dst = (unsigned char*)dstptr;
  const unsigned char* src = (const unsigned char*)srcptr;
  if (dst < src) {
    for (size_t i = 0; i < size; i++)
      dst[i] = src[i];
  } else {
    for (size_t i = size; i != 0; i--)
      dst[i - 1] = src[i - 1];
  }
  return dstptr;
}

void* memset(void* s, int c, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((char*)s)[i] = (char)c;
  }

  return s;
}

char* strrev(char* s) {
  usize len = strlen(s);
  for (usize i = 0; i < len / 2; i++) {

    // swap
    char temp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = temp;
  }

  return s;
}

char* strcat(char* dst, const char* src) {
  usize src_i = 0;
  const usize src_len = strlen(src);
  usize dst_i = strlen(dst);

  for (; src_i < src_len; src_i++) {
    dst[dst_i] = src[src_i];
    dst_i++;
  }

  return dst + dst_i;
}
