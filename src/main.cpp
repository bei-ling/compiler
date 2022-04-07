
#include <stdio.h>
#include "lex.h"
#include "thompson.h"

int main(int argc, char** argv)
{   
    char pattern[] = "a+(b|c)\0";
    vector<string> inputs;

    inputs.push_back("ab");
    inputs.push_back("ac");
    inputs.push_back("abbb");
    inputs.push_back("abc");
    inputs.push_back("accc");

    char filePath[] = "input.c";
    char *fileData;
    int fileLength;
    
    // LexProc(filePath, fileData, fileLength);

    LexParse(pattern, inputs);
 
    return 0;
}