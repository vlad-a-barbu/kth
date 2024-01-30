char s[] = {
  
  10,
  0
};

#include <stdio.h>

int main() {
    int i;

    printf("char s[] = {\n");
    for(i = 0; s[i]; i++)
        printf("\t%d,\n", s[i]);
    printf("\t0\n};\n\n");
    printf("%s", s);
    return 0;
}
