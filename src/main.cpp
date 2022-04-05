
#include <stdio.h>
#include "lex.h"

int main(int argc, char** argv)
{   
    char pattern[] = "i+f\0";
    vector<string> inputs;

    inputs.push_back("sf");
    inputs.push_back("ifsa");
    inputs.push_back("if");
    inputs.push_back("ef");
    inputs.push_back("fe");

    char filePath[] = "input.c";
    char *fileData;
    int fileLength;
    
    LexProc(filePath, fileData, fileLength);

    return 0;
}