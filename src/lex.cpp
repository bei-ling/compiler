#include "base_define.h"
#include "thompson.h"
#include "lex.h"

unordered_map<TokenType, string> TokenTypeMap = {
    {T_INDENTIFIER, "identifier"},
    {T_IF, "if"},
    {T_WHILE, "while"},

    {T_L_PAREN, "l_paren"},
    {T_R_PAREN, "r_paren"},
    {T_L_BRACE, "l_brace"},
    {T_R_BRACE, "r_brace"},

    {T_INT, "int"},
    {T_EQUAL, "equal"},
    {T_EQUALEQUAL, "equalequal"},
    {T_NUMERIC_CONSTANT, "numeric_constant"},
    {T_SEMI, "semi"},
    {T_ASSIGN, "assign"},

    {T_RETURN, "return"},
    {T_PLUS, "plus"},
    {T_EOF, "eof"}
};

unordered_map<string, TokenType> IndentifierMap = {
    {"if", T_IF},
    {"while", T_WHILE},
    {"int", T_INT},
    {"main", T_INDENTIFIER},
    {"return", T_RETURN}
};

TokenPosition g_tokenPos;

int PrintTokenInfor(string& token, TokenType tokenType, int lineNo)
{
    cout << TokenTypeMap[tokenType]  << " '" << token
        << "'\t Loc<" << g_tokenPos.row << ">" << endl;
    return SUCCESS;
}



int Proc_T_INDENTIFIER(char* &inputs)
{
    string token = "";
    while (*inputs != '\0' && *inputs != ' ' && *inputs != '\n' &&
        ((*inputs >= 'a' && *inputs <= 'z') || (*inputs >= 'A' && *inputs <= 'Z') ||
        *inputs == '_' || (*inputs >= '0' && *inputs <= '9'))) {

        token += *inputs;
        ++inputs;
    }
    if (IndentifierMap[token]) {
        PrintTokenInfor(token, IndentifierMap[token], g_tokenPos.row);
        return SUCCESS;
    }
    PrintTokenInfor(token, T_INDENTIFIER, g_tokenPos.row);
    return SUCCESS;
}

int proc_T_PAREN_BRACE(char ch)
{
    TokenType type = T_INDENTIFIER;
    switch(ch) {
        case '(':
            type = T_L_PAREN;
            break;
        case ')':
            type = T_R_PAREN;
            break;
        case '{':
            type = T_L_BRACE;
            break;
        case '}':
            type = T_R_BRACE;
            break;
        case ';':
            type = T_SEMI;
            break;
    }
    cout << TokenTypeMap[type] << " " << ch << "\t" << g_tokenPos.row << endl;
    return SUCCESS;
}

int Proc_T_NUMERIC_CONSTANT(char* inputs)
{
    return SUCCESS;
}

int proc_T_SEMI(char* inputs)
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
 
    while (*inputs != '\0') {
        switch (*inputs) {
        
            case '\0': // 字符串开头
                inputs++;
                break;

            case '\n': case '\r':
                g_tokenPos.row += 1;
                inputs += 2;
                break;

            case '=': case '*':
            case '+': case '-':
            case '"': case '\\':
                inputs++;
                break;

            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                Proc_T_NUMERIC_CONSTANT(inputs);
                inputs++;
                break;

            case ' ': case '\t':
                inputs++;
                break;
                
            case ';': case '(': case ')': case '{': case '}':
                proc_T_PAREN_BRACE(*inputs);
                inputs++;
                break;

            default:
                if ((*inputs >= 'a' && *inputs <= 'z') || (*inputs >= 'A' && *inputs <= 'Z') ||
                    *inputs == '_' || (*inputs >= '0' && *inputs <= '9')) {
                    Proc_T_INDENTIFIER(inputs);
                } else {
                    inputs++;
                }
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

int InitLexProcParas()
{
    memset(&g_tokenPos, 0, sizeof(g_tokenPos));
    PRINT_LOG_INFO("InitLexProcParas SUCCESS!");
    return SUCCESS;
}

int LexProc(char filePath[], char* &fileData, int &fileLength)
{
    FileReadLines(filePath, fileData, fileLength);
    next(fileData, fileLength);
    free(fileData);
    return SUCCESS;
}
