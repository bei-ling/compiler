#include "base_define.h"
#include "lex.h"

unordered_map<TokenType, string> TokenMap = {
    {T_INDENTIFIER, "identifier"},
    {T_L_PAREN, "l_paren"},
    {T_R_PRAEN, "r_paren"},
    {T_L_BRACE, "l_brace"},
    {T_R_BRACE, "r_brace"},

    {T_INT, "int"},
    {T_EQUAL, "equal"},
    {T_NUMERIC_CONSTANT, "numeric_constant"},
    {T_SEMI, "semi"},
    {T_ASSIGN, "assign"},

    {T_RETURN, "return"},
    {T_PLUS, "plus"},
    {T_EOF, "eof"},
};


 
int ProcNumber(char* inputs)
{

    return SUCCESS;
}



int procSemi(char* inputs)
{
    return SUCCESS;
}
int ProcPlus(char* inputs)
{

    return SUCCESS;
}

int next(char* &fileData, int &fileLength)
{

    char* inputs = fileData;
    for (int i = 0; i < fileLength; ++i) {
        printf("%c", *(inputs+i));
    }
    while (*inputs != '\0') {
        switch (*inputs) {

            case '\0': // 字符串开头
                break;

            case '\n':
            case ' ': case '(': case ')': case '{': case '}':
                putchar(*inputs);
                inputs++;
                break;

            case '=': case '*':
            case '+':
                break;

            case ';':
                procSemi(inputs);
    



            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                ProcNumber(inputs);
            
            default:
                inputs++;
                break;
        }
    }

    return SUCCESS;
}

 
int FileReadLines(char filePath[], char* &fileData, int &fileLength)
{
    FILE *fp;
    fp = fopen(filePath, "r");
    if (fp == NULL) {
        PRINT_LOG_ERRO("failed to read this file: %s", filePath);
        return FAIL;
    }
    PRINT_LOG_INFO("loading this file: %s", filePath);

    fseek(fp, 0, SEEK_END);
    fileLength = ftell(fp);
    fileData = (char*)malloc((fileLength+1) * sizeof(char)); 
    rewind(fp);

    fileLength = fread(fileData, 1, fileLength, fp);
    fileData[fileLength] = '\0';

    fclose(fp);
    return SUCCESS;
}


int LexProc(char filePath[], char* &fileData, int &fileLength)
{
    FileReadLines(filePath, fileData, fileLength);
    next(fileData, fileLength);
    free(fileData);
    return SUCCESS;
}
