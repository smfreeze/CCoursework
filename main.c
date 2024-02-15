#include <errno.h>
#include <stdlib.h>

#include <msString.h>
#include <functions.h>

int main(int argc, char **argv) {

  /* TASK 1: */

  /* printBytes example 1: */
  double data1 = 5000;
  void *pointer1 = &data1;
  printBytes(pointer1, sizeof(data1));

  /* printBytes example 2: */
  char data2[] = {'X', 2, 3, 'A'};
  void *pointer2 = &data2;
  printBytes(pointer2, sizeof(data2));

  /* TASK 2: */
  FILE *fpread;
  FILE *fpwrite;

  if ((fpread = fopen(argv[1], "r")) == NULL) {
    printf("Unable to open file for read access.\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  fseek(fpread, 0, SEEK_END);
  long fileSize = ftell(fpread);
  rewind(fpread);

  char *str = malloc(fileSize + 1);
  if (str == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  if ((fpwrite = fopen(argv[2], "w")) == NULL) {
    printf("Unable to open file for write access.\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  if (fgets(str, fileSize + 1, fpread) == NULL) {
    printf("Error reading file\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  reverse(str);

  if (str[0] == '\n'){
    memmove(str,str+1,fileSize);
  }

  if (fputs(str, fpwrite) == EOF) {
    printf("Error writing to file\n");
    fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
    exit(1);
  }

  fclose(fpread);
  fclose(fpwrite);
 
  free(str);

  return 0;
}
