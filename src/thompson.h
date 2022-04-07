#ifndef _THOMPSON_H_
#define _THOMPSON_H_
#include "base_define.h"

#define SUCCESS 1
#define FAIL 0
#define GET_ENUM_STRING(value) #value

#define op_push(s, v) (s.value[s.top++] = v)
#define op_pop(s) (--s.top)
#define op_top(s) (s.value[s.top - 1])

#define data_push(s, v) (s.value[s.top++] = v)
#define data_pop(s) (--s.top)
#define data_top(s) (s.value[s.top - 1])

typedef enum {
    CHAR_DFA = 0,
    CHAR_A_OR_CHAR_B,
    CHAR_MORE,
    CHAR_A_CONC_CHAR_B,
    CHAR_CLOSURE,
} NFADefine;


typedef struct GraphEdge {
    int vex;
    char value;
    GraphEdge* next;
} GraphEdge;

typedef struct GraphNode {
    int adj;
    GraphEdge* firstEdge;
} GraphNode;

typedef struct State {
    int start;
    int end;
    int type;
} NfaState;

int NfaResultPrint();
int ThompsonConstruct(char inputs[]);
int LexParse(char pattern[], vector<string> &inputs);
#endif