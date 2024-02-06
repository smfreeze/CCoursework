#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000000

void printBytes(void *, int);
void reverse(char *);

int main(int argc, char **argv) {

  // TASK 1:
  //
  //
  //
  //
  // printBytes example 1:
  double data1 = 5000;
  void *pointer1 = &data1;
  printBytes(pointer1, sizeof(data1));

  // printBytes example 2:
  char data2[] = {'X', 2, 3, 'A'};
  void *pointer2 = &data2;
  printBytes(pointer2, sizeof(data2));

  // TASK 2:
  //
  //
  //
  //
  FILE *fpread;
  FILE *fpwrite;
  char str[MAX_SIZE];

  if ((fpread = fopen(argv[1], "r")) == NULL) {
    printf("Unable to open file for read access.\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  if ((fpwrite = fopen(argv[2], "w")) == NULL) {
    printf("Unable to open file for write access.\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  if (fgets(str, MAX_SIZE, fpread) == NULL) {
    printf("Error reading file\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  reverse(str);

  if (fputs(str, fpwrite) == EOF) {
    printf("Error writing to file\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  fclose(fpread);
  fclose(fpwrite);

  return 0;
}

void reverse(char *str) {
  int length = strlen(str);
  for (int i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}

void printBytes(void *ptr, int numBytes) {
  unsigned char *bytePtr = (unsigned char *)ptr;
  printf("Starting at memory address %p:\n", ptr);
  for (int i = 0; i < numBytes; bytePtr++, i++) {
    printf("%03d: %d\n", i + 1, *bytePtr);
  }
}
