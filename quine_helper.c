#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("pass path to quine - src buffer will be appended as 's[]'\n");
        return 1;
    }
    
    FILE *f;
    errno_t err = fopen_s(&f, *(argv + 1), "rb+");
    if (err != 0) {
        printf("fopen errno %d\n", err);
        return 1;
    }

    fseek(f, 0L, SEEK_END);
    size_t fsize = ftell(f);
    rewind(f);

    char* fbuff = malloc(fsize + 1);
    if (fbuff == NULL) {
        printf("fbuff malloc failed\n");
        fclose(f);
        return 1;
    }
    fread(fbuff, sizeof(char), fsize, f);
    fbuff[fsize] = '\0';
     
    size_t qsize = 7 * fsize + 18;
    char *qbuff = malloc(qsize);
    if (qbuff == NULL) {
        printf("qbuff malloc failed\n");
        free(fbuff);
        fclose(f);
        return 1;
    }

    size_t length = 0, written = 0, remaining = qsize;
    length += snprintf(qbuff + length, remaining, "char s[] = {\n");
    remaining = qsize - length;
    for (size_t i = 0; i < fsize; ++i) {
        written = snprintf(qbuff + length, remaining, "\t%d,\n", fbuff[i]);
        if (written < 0 || written >= remaining) {
            printf("qbuff overflow\n");
            fclose(f);
            free(fbuff);
            free(qbuff);
            return 1;
        }
        length += written;
        remaining -= written;
    }
    written = snprintf(qbuff + length, remaining, "};\n\n%s", fbuff);
    if (written < 0 || written >= remaining) {
        printf("qbuff overflow\n");
        fclose(f);
        free(fbuff);
        free(qbuff);
        return 1;
    }
    length += written;
    remaining -= written;

    rewind(f);
    fwrite(qbuff, sizeof(char), length, f);

    fclose(f);
    free(fbuff);
    free(qbuff);

    return 0;
}
