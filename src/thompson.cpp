
#include "thompson.h"
#include "subset_cons.h"

int g_nfaNodeId = 0;

typedef struct {
    int top;
    char value[1024];
} OpStack;

typedef struct {
    int top;
    NfaState* value[1024];
} DataStack;

unordered_map<char, int> priority;
OpStack op_stack; 
DataStack data_stack;

GraphNode* g_nfaGraph[256];


int proc_CHAR_A_OR_CHAR_B()
{
    NfaState* state = (NfaState*)malloc(sizeof(NfaState));
    GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));

    g_nfaGraph[g_nfaNodeId] = node1;
    g_nfaGraph[g_nfaNodeId+1] = node2;

    GraphEdge* edge1 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge2 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge3 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge4 = (GraphEdge*)malloc(sizeof(GraphEdge));

    NfaState* s1 = data_top(data_stack);
    data_pop(data_stack);
    NfaState* s2 = data_top(data_stack);
    data_pop(data_stack);

    node1->firstEdge = edge1;
    edge1->next = edge2;
    edge1->vex = s1->start;
    edge1->value = '$';
    
    edge2->next = NULL;
    edge2->vex = s2->start;
    edge2->value = '$';
    
    g_nfaGraph[s1->end]->firstEdge = edge3;
    edge3->next = NULL;
    edge3->value = '$';
    edge3->vex = g_nfaNodeId + 1;

    g_nfaGraph[s2->end]->firstEdge = edge4;
    edge4->next = NULL;
    edge4->value = '$';
    edge4->vex = g_nfaNodeId + 1;

    state->start = g_nfaNodeId;
    state->end = g_nfaNodeId + 1;
    state->type = CHAR_A_OR_CHAR_B;
    g_nfaNodeId += 2;
    
    data_push(data_stack, state);
    return SUCCESS;
}
int proc_CHAR_CLOSURE()
{
    NfaState* state = (NfaState*)malloc(sizeof(NfaState));

    GraphEdge* edge1 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge2 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge3 = (GraphEdge*)malloc(sizeof(GraphEdge));
    GraphEdge* edge4 = (GraphEdge*)malloc(sizeof(GraphEdge));

    GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));

    NfaState* s = data_top(data_stack);
    data_pop(data_stack);

    g_nfaGraph[g_nfaNodeId] = node1;
    g_nfaGraph[g_nfaNodeId+1] = node2;

    node1->adj = g_nfaNodeId;
    node1->firstEdge = edge1;
    edge1->value = '$';
    edge1->vex = s->start;
    edge1->next = edge2;
    edge2->value = '$';
    edge2->vex = g_nfaNodeId + 1;
    edge2->next = NULL; 

    node2->adj = g_nfaNodeId + 1;
    node2->firstEdge = NULL;

    g_nfaGraph[s->end]->firstEdge = edge3;
    edge3->next = edge4;
    edge3->value = '$';
    edge3->vex = g_nfaNodeId + 1;

    edge4->next = NULL;
    edge4->value = '$';
    edge4->vex = s->start;

    state->start = g_nfaNodeId;
    state->end = g_nfaNodeId + 1;
    state->type = CHAR_CLOSURE;
    g_nfaNodeId += 2;
    data_push(data_stack, state);
    return 0;
}

int proc_CHAR_A_CONC_CHAR_B()
{
   
    NfaState* state = (NfaState*)malloc(sizeof(NfaState));
    NfaState* s1 = data_top(data_stack);
    data_pop(data_stack);
    NfaState* s2 = data_top(data_stack);
    data_pop(data_stack);

    g_nfaGraph[s2->end]->firstEdge = g_nfaGraph[s1->start]->firstEdge;
    g_nfaGraph[s1->start]->firstEdge = NULL;

    state->start = s2->start;
    state->end = s1->end;
    state->type = CHAR_A_CONC_CHAR_B;
    data_push(data_stack, state);
    return 0;
}
 

int symbol_proc(char symbol)
{
    GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));
    GraphEdge* edge = (GraphEdge*)malloc(sizeof(GraphEdge));
    NfaState* state = (NfaState*)malloc(sizeof(NfaState));
    g_nfaGraph[g_nfaNodeId] = node1;
    g_nfaGraph[g_nfaNodeId + 1] = node2;

    node1->adj = g_nfaNodeId;
    node1->firstEdge = edge;
    edge->next = NULL;
    edge->vex = g_nfaNodeId + 1;
    edge->value = symbol;

    node2->adj = g_nfaNodeId + 1;
    node2->firstEdge = NULL;
    
    state->start = g_nfaNodeId;
    state->end = g_nfaNodeId + 1;
    state->type = CHAR_DFA;
    g_nfaNodeId += 2;

    data_push(data_stack, state);
    return 0;
}

int proc_op(char op)
{
 
    switch (op) {

        case '|':
            proc_CHAR_A_OR_CHAR_B();
            break;
            
        case '*': 
            proc_CHAR_CLOSURE();
            break;
        case '+':
            proc_CHAR_A_CONC_CHAR_B();
            break;
        default:
            break;
    }
    return SUCCESS;
}

int op_detect(char ch) 
{
    char op = op_top(op_stack);
    while (op_stack.top != 0 && priority[ch] <= priority[op]) { // 如果小于栈顶优先级，就op_stack退栈，并计算
        op_pop(op_stack);
        proc_op(op);
        op = op_top(op_stack);
    }
    op_push(op_stack, ch);
    return SUCCESS;
}

int char_proc(char symbol)
{
    char op;
  

    // 主要看操作符栈顶的元素
    switch (symbol) {
        
        case '(':
            op_push(op_stack, symbol);
            break;
        case ')':
            op = op_top(op_stack);
            while (op  != '(') {
                op_pop(op_stack);
                proc_op(op);
                op = op_top(op_stack);
            }
            op_pop(op_stack); // (退栈
            break;
        case '|':
            op_detect(symbol);
            break;

        case '*':
            proc_op(symbol);
            break;
        case '+':
            op_detect(symbol);
            break;

        default:
            symbol_proc(symbol);
            break;
    }
    return SUCCESS;
}

void InitConstructInfo()
{
    op_stack.top = 0;
    data_stack.top = 0;

    priority['('] = 0;
    priority[')'] = 4;
    priority['|'] = 1;
    priority['+'] = 2;
    priority['*'] = 3;
}
 
int NfaResultPrint()
{   
    for (int i = 0; i < g_nfaNodeId; ++i) {
        GraphEdge* edge = g_nfaGraph[i]->firstEdge;
        GraphEdge* p;
        while (edge != NULL ) {
            // printf("%d, %d, %c\n", i, edge->vex, edge->value);
            p = edge;
            edge = edge->next;
            free(p);
        }
        free(g_nfaGraph[i]);
    }
    return SUCCESS;
}


int ThompsonConstruct(char inputs[])
{
    InitConstructInfo();
    for (int i = 0; i < strlen(inputs) || (op_stack.top != 0); ++i) {
        if (i < strlen(inputs)) {
            char_proc(inputs[i]);
            continue;
        }
        char ch = op_top(op_stack);
        proc_op(ch);
        op_pop(op_stack);
    }
    return SUCCESS;
}

int LexParser(char pattern[], vector<string> &inputs) 
{   
    printf("pattern: %s\n", pattern);

    ThompsonConstruct(pattern);
    printf("data_stack size: %d\n", data_stack.top);
    NfaState* s = data_top(data_stack);
    data_pop(data_stack);
    printf("begin: %d, end: %d\n", s->start, s->end);
    SubSetConstruction(g_nfaGraph, s->start, s->end, inputs);
    NfaResultPrint();
    return 0;
}
