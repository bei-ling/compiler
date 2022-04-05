
#include <stdio.h>
#include "thompson.h"
#include "lex.h"

int main(int argc, char** argv)
{   
    // char pattern[] = "#+d+e+f+i+n+e\0";
    // vector<string> inputs;

    // inputs.push_back("thb");
    // inputs.push_back("mb");
    // inputs.push_back("#desine");
    // inputs.push_back("#defines");
    // inputs.push_back("#define");

    // LexParser(pattern, inputs);
    char filePath[] = "input.c";
    char *fileData;
    int fileLength;
    
    LexProc(filePath, fileData, fileLength);

    return 0;
}