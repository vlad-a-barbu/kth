#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3) return 1;
  char *from = *(argv + 1);
  char *to = *(argv + 2);

  FILE *fromf, *tof;
  fopen_s(&fromf, from, "r");
  fopen_s(&tof, to, "w");
  
  fprintf(tof, "char s[] = {\n");
  int ch;
  while ((ch = fgetc(fromf)) != -1) {
    fprintf(tof, "\t%d,\n", ch);
  }
  fprintf(tof, "};\n\n");
  
  fclose(fromf);
  fclose(tof);

  return 0;
}
