
#ifndef _LEX_H_
#define _LEX_H_

#include "base_define.h"

typedef enum {

    T_INDENTIFIER = 1,

    T_IF,
    T_WHILE,

    T_L_PAREN,          // (
    T_R_PAREN,          // )
    T_L_BRACE,          // {
    T_R_BRACE,          // }

    T_INT,
    T_EQUAL,            // =
    T_EQUALEQUAL,  
    T_NUMERIC_CONSTANT, // 1
    T_SEMI,             // ; 分号
    T_ASSIGN,           // = 赋值

    T_RETURN,           // return
    T_PLUS,             // +
    T_EOF,              // ''
    
} TokenType;

typedef struct {
    int row;
    int col;
} TokenPosition;


int LexProc(char filePath[], char* &fileData, int &fileLength);

#endif