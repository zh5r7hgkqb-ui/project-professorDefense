#include <stdio.h>

void printAscii(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("%s 파일을 찾을 수 없습니다!\n", filename);
        return;
    }

    char line[2048];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}
