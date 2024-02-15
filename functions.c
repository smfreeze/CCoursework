#include <string.h>
#include <stdio.h>

#include <functions.h>

extern void printBytes(void *ptr, int numBytes) {
  unsigned char *bytePtr = (unsigned char *)ptr;
  printf("Starting at memory address %p:\n", ptr);
  int i;
  for (i = 0; i < numBytes; bytePtr++, i++) {
    printf("%03d: %d\n", i + 1, *bytePtr);
  }
}

extern void reverse(char *str) {
  int length = strlen(str);
  int i;
  for (i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}
