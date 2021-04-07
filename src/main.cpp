
#include "pch.h"
#include "test1.h"
#include "test2.h"
#include "test3.h"
#include "test4.h"

int main(int argc, char** argv)
{
    char ch;
    FILE* fi, *fo;
    fi = fo = NULL;
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

    return 0;
}