#ifndef _SUBSET_CONS_H_
#define _SUBSET_CONS_H_
#include "thompson.h"


using std::set;
using std::vector;
using std::map;
typedef struct DfaTable {
    set<int> beginState;
    char trans;
    set<int> endState;

} DfaTable;

typedef struct DFARegState {
    int beginState;
    int endState;
} DFARegState;


int SubSetConstruction(GraphNode** graph, int start, int end, string& inputs);
#endif