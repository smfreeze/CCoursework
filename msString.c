#include <msString.h>

extern msString msSetString(char *str) {
  long int length = strlen(str);
  msString newString = malloc(sizeof(long int) + length * sizeof(char));
  if (newString == NULL) {
    msError("Memory allocation failed");
  }
  memcpy(newString, &length, sizeof(long int));
  memcpy(newString + sizeof(long int), str, length * sizeof(char));
  return newString;
};

extern char *msGetString(msString ms) {
  long int length;
  memcpy(&length, ms, sizeof(long int));
  char *str = malloc(length + 1);
  if (str == NULL) {
    msError("Memory allocation failed");
  }
  memcpy(str, ms + sizeof(long int), length);
  str[length] = '\0';
  return str;
};

extern void msCopy(msString *dest, msString src) {
  long int length = *((long int *)src);
  *dest = malloc(sizeof(long int) + length * sizeof(char));
  if (*dest == NULL) {
    msError("Memory allocation failed");
  }
  memcpy(*dest, src, sizeof(long int) + length * sizeof(char));
}

extern void msConcatenate(msString *dest, msString src) {
  long int destLength = msLength(*dest);
  long int srcLength = msLength(src);

  msString newString =
      malloc(sizeof(long int) + (destLength + srcLength) * sizeof(char));
  if (newString == NULL) {
    msError("Memory allocation failed");
  }

  long int concatenatedLength = destLength + srcLength;
  memcpy(newString, &concatenatedLength, sizeof(long int));
  memcpy(newString + sizeof(long int), *dest + sizeof(long int), destLength);
  memcpy(newString + sizeof(long int) + destLength, src + sizeof(long int),
         srcLength);

  free(*dest); /*Memory leak fix*/
  *dest = newString;
}

extern long int msLength(msString ms) {
  long int length;
  memcpy(&length, ms, sizeof(long int));
  return length;
}

extern int msCompare(msString str1, msString str2) {
  long int length1 = *((long int *)str1);
  long int length2 = *((long int *)str2);

  if (length1 != length2) {
    return 1;
  }

  return memcmp(str1 + sizeof(long int), str2 + sizeof(long int), length1) != 0
             ? 1
             : 0;
}

extern int msCompareString(msString ms, char *str) {
  long int length = *((long int *)ms);
  if (strlen(str) != length) {
    return 1;
  }
  return memcmp(ms + sizeof(long int), str, length) != 0 ? 1 : 0;
}

static void msError(char *message) {
  fprintf(stderr, "Error: %s\n", message);
  exit(1);
}
