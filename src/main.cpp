
#include <stdio.h>
#include "thompson.h"


int main(int argc, char** argv)
{   
    char pattern[] = "#+d+e+f+i+n+e\0";
    vector<string> inputs;

    inputs.push_back("thb");
    inputs.push_back("mb");
    inputs.push_back("ththbs");
    inputs.push_back("thbs");
    inputs.push_back("#define");

    LexParser(pattern, inputs);
 
    return 0;
}