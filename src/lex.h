
#ifndef _LEX_H_
#define _LEX_H_

#include "base_define.h"

typedef enum {

    T_INDENTIFIER = 0,
    T_L_PAREN,          // (
    T_R_PRAEN,          // )
    T_L_BRACE,          // {
    T_R_BRACE,          // }

    T_INT,
    T_EQUAL,            // ==
    T_NUMERIC_CONSTANT, // 1
    T_SEMI,             // ; 分号
    T_ASSIGN,           // = 赋值

    T_RETURN,           // return
    T_PLUS,             // +
    T_EOF,              // ''
    
} TokenType;


typedef struct {
    int x;
} ToKenInfo; 

int LexProc(char filePath[], char* &fileData, int &fileLength);

#endif