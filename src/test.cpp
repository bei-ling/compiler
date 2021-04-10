

#include "test.h"

int read_file()
{
    char ch;
    FILE* fi, *fo;
    fi = fo = NULL;
    // load file
    fi = fopen("/mnt/e/HiCode/c_compiler/code/input.txt", "r+");
    fo = fopen("/mnt/e/HiCode/c_compiler/code/output.txt", "w+");
    if (fi == NULL) {
        printf("open file fail...\n");
        return 0;
    }


    while ((ch = fgetc(fi)) != EOF) {
        fputc(ch, fo);
    }


    fclose(fi);
    fclose(fo);
    printf("hello world!\n");
    return 0;
}