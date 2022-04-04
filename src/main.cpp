
#include <stdio.h>
#include "thompson.h"


int FileReadLines(char filePath[], string &lines)
{
    ifstream rf(filePath);
    string line;
    if (!rf.is_open()) {
        PRINT_LOG_ERRO("failed to read this file %s", filePath);
        return FAIL;
    }
    while (getline(rf, line)){
        // lines += line;
        printf("%s", line.c_str());
 
    }
    rf.close();
    return SUCCESS;
}


int next()
{

    while (1) {
        break;
    }
    return SUCCESS;
}

 


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
    char filePath[] = "input.txt";
    string Content = "";
    FileReadLines(filePath, Content);
  
    return 0;
}